#include "StdInc.h"

#include "ClientCheckpoint.h"

ClientCheckpoint::ClientCheckpoint(ClientMarker* thisMarker)
{
	this->thisMarker = thisMarker;
	checkpoint = NULL;
	streamedIn = false;
	visible = true;
	icon = ClientCheckpoint::ICON_NONE;
	color = SColorRGBA(255, 0, 0, 255);
	size = 4.0f;
	type = CHECKPOINT_EMPTYTUBE;
	direction.fX = 1.0f;
	isHaveTarget = false;
}

ClientCheckpoint::~ClientCheckpoint()
{
	destroy();
}

unsigned long ClientCheckpoint::getCheckpointType() const
{
	switch (type)
	{
	case CHECKPOINT_TUBE:
	case CHECKPOINT_EMPTYTUBE:
	case CHECKPOINT_ENDTUBE:
		return ClientCheckpoint::TYPE_NORMAL;

	case CHECKPOINT_TORUS:
		return ClientCheckpoint::TYPE_RING;

	default:
		return ClientCheckpoint::TYPE_INVALID;
	}
}

void ClientCheckpoint::setCheckpointType(unsigned long type)
{
	unsigned long newType;

	switch (type)
	{
	case ClientCheckpoint::TYPE_NORMAL:
	{
		if (icon == ClientCheckpoint::ICON_ARROW)
			newType = CHECKPOINT_TUBE;
		else if (icon == ClientCheckpoint::ICON_FINISH)
			newType = CHECKPOINT_ENDTUBE;
		else
			newType = CHECKPOINT_EMPTYTUBE;

		break;
	}

	case ClientCheckpoint::TYPE_RING:
	{
		newType = CHECKPOINT_TORUS;

		break;
	}

	default:
	{
		if (icon == ClientCheckpoint::ICON_ARROW)
			newType = CHECKPOINT_TUBE;
		else if (icon == ClientCheckpoint::ICON_FINISH)
			newType = CHECKPOINT_ENDTUBE;
		else
			newType = CHECKPOINT_EMPTYTUBE;

		break;
	}
	}

	if (this->type != newType)
	{
		this->type = newType;

		recreate();
	}
}

void ClientCheckpoint::setPosition(const CVector& position)
{
	if (matrix.vPos != position)
	{
		if (targetPosition.fX != 0 && targetPosition.fY != 0 && targetPosition.fZ != 0)
		{
			direction = targetPosition - position;
			direction.Normalize();
		}

		matrix.vPos = position;

		recreateWithSameIdentifier();
	}
}

void ClientCheckpoint::setDirection(const CVector& direction)
{
	if (this->direction != direction)
	{
		targetPosition = CVector(0.0f, 0.0f, 0.0f);
		this->direction = direction;

		if (getCheckpointType() == ClientCheckpoint::TYPE_RING || icon == ClientCheckpoint::ICON_ARROW)
			recreate();
	}
}

void ClientCheckpoint::getMatrix(CMatrix& matrix)
{
	matrix = this->matrix;
}

void ClientCheckpoint::setMatrix(CMatrix& matrix)
{
	setPosition(matrix.vPos);
	this->matrix = matrix;
}

void ClientCheckpoint::setNextPosition(const CVector& position)
{
	if (targetPosition != position)
	{
		targetPosition = position;
		direction = targetPosition - matrix.vPos;
		direction.Normalize();

		if (getCheckpointType() == ClientCheckpoint::TYPE_RING || icon == ClientCheckpoint::ICON_ARROW)
			recreate();
	}
}

void ClientCheckpoint::setVisible(bool visible)
{
	if (isStreamedIn())
	{
		if (!visible && this->visible)
			destroy();
		else if (visible && this->visible)
			create();
	}

	this->visible = visible;
}

void ClientCheckpoint::setIcon(unsigned int icon)
{
	if (this->icon != icon)
	{
		this->icon = icon;

		if (getCheckpointType() == ClientCheckpoint::TYPE_NORMAL)
		{
			unsigned long newType;

			switch (icon)
			{
			case ClientCheckpoint::ICON_NONE:
				newType = CHECKPOINT_EMPTYTUBE;
				break;

			case ClientCheckpoint::ICON_ARROW:
				newType = CHECKPOINT_TUBE;
				break;

			case ClientCheckpoint::ICON_FINISH:
				newType = CHECKPOINT_ENDTUBE;
				break;

			default:
				newType = CHECKPOINT_EMPTYTUBE;
				break;
			}

			if (newType != type)
			{
				type = newType;

				recreate();
			}
		}
	}
}

void ClientCheckpoint::setColor(const SColor& color)
{
	if (this->color != color)
	{
		this->color = color;

		recreate();
	}
}

void ClientCheckpoint::setSize(float size)
{
	if (this->size != size)
	{
		this->size = size;

		recreate();
	}
}

unsigned char ClientCheckpoint::stringToIcon(const char* string)
{
	if (stricmp(string, "none") == 0)
		return ICON_NONE;
	else if (stricmp(string, "arrow") == 0)
		return ICON_ARROW;
	else if (stricmp(string, "finish") == 0)
		return ICON_FINISH;

	return ICON_INVALID;
}

void ClientCheckpoint::streamIn()
{
	streamedIn = true;

	if (visible)
		create();
}

void ClientCheckpoint::streamOut()
{
	destroy();

	streamedIn = false;
}

void ClientCheckpoint::create(unsigned long id)
{
	if (checkpoint == NULL)
	{
		static unsigned long staticId = 128;

		if (id == 0)
		{
			++staticId;
			this->id = staticId;
		}
		else
			this->id = id;

		checkpoint = game->GetCheckpoints()->CreateCheckpoint(this->id, static_cast<WORD>(type), &matrix.vPos, &direction, size, 0.2f, color);

		if (checkpoint)
			checkpoint->SetRotateRate(0);
	}
}

void ClientCheckpoint::destroy()
{
	if (checkpoint != NULL)
	{
		checkpoint->Remove();
		checkpoint = NULL;
	}
}

void ClientCheckpoint::recreate()
{
	if (isStreamedIn() && visible)
	{
		destroy();
		create();
	}
}

void ClientCheckpoint::recreateWithSameIdentifier()
{
	if (isStreamedIn() && visible)
	{
		destroy();
		create(id);
	}
}
