#include "StdInc.h"

#include "ClientEntity.h"

ClientEntity::ClientEntity(int id, bool local) : ClassInit(this)
{
	this->id = id;
	this->local = local;
}

ClientEntity::~ClientEntity()
{

}

void ClientEntity::setID(int id)
{
	this->id = id;
}

bool ClientEntity::getMatrix(CMatrix& matrix) const
{
	CEntity* entity = const_cast<CEntity*>(getGameEntity());

	if (entity)
	{
		if (entity->GetMatrix(&matrix))
			return true;
	}

	CVector rotation;

	getRotationRadians(rotation);

	ConvertRadiansToDegreesNoWrap(rotation);
	rotation = ConvertEulerRotationOrder(rotation, EULER_ZXY, EULER_MINUS_ZYX);
	ConvertRadiansToDegreesNoWrap(rotation);

	multiplayer->ConvertEulerAnglesToMatrix(matrix, rotation.fX, rotation.fY, rotation.fZ);
	getPosition(matrix.vPos);

	return true;
}

bool ClientEntity::setMatrix(const CMatrix& matrix)
{
	CEntity* entity = const_cast<CEntity*>(getGameEntity());

	if (entity)
	{
		entity->SetMatrix(const_cast<CMatrix*>(&matrix));

		return true;
	}

	setPosition(matrix.vPos);

	CVector rotation;

	multiplayer->ConvertEulerAnglesToMatrix(const_cast<CMatrix&>(matrix), rotation.fX, rotation.fY, rotation.fZ);

	ConvertRadiansToDegreesNoWrap(rotation);
	rotation = ConvertEulerRotationOrder(rotation, EULER_MINUS_ZYX, EULER_ZXY);
	ConvertRadiansToDegreesNoWrap(rotation);

	setRotationRadians(rotation);

	return true;
}

void ClientEntity::getRotationRadians(CVector& outRadians) const
{
	outRadians = CVector();
}

void ClientEntity::setRotationRadians(const CVector& radians)
{

}

bool ClientEntity::isDoubleSided()
{
	//return doubleSided;
	return false;
}

void ClientEntity::setDoubleSided(bool doubleSided)
{
	/*doubleSidedInit = true;
	this->doubleSided = doubleSided;*/
}

CSphere ClientEntity::getWorldBoundingSphere()
{
	CVector position;

	getPosition(position);

	return CSphere(position, 0.f);
}

float ClientEntity::getDistanceBetweenBoundingSpheres(ClientEntity* other)
{
	CSphere sphere = getWorldBoundingSphere();
	CSphere otherSphere = getWorldBoundingSphere();

	return (sphere.vecPosition - otherSphere.vecPosition).Length() - sphere.fRadius - otherSphere.fRadius;
}
