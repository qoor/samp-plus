#pragma once

class ClientMarkerCommon
{
public:
	enum
	{
		CLASS_CHECKPOINT,
		CLASS_3DMARKER,
		CLASS_CORONA
	};

	enum
	{
		ICON_NONE,
		ICON_ARROW,
		ICON_FINISH,
		ICON_INVALID
	};

	ClientMarkerCommon();
	virtual ~ClientMarkerCommon();

	virtual void doPulse();
	virtual unsigned int getMarkerType() const = 0;

	virtual bool isVisible() const = 0;
	virtual void setVisible(bool visible) = 0;

	virtual SColor getColor() const = 0;
	virtual void setColor(const SColor& color) = 0;

	virtual void getPosition(CVector& position) const = 0;
	virtual void setPosition(const CVector& position) = 0;

	virtual void getMatrix(CMatrix& matrix) = 0;
	virtual void setMatrix(CMatrix& matrix) = 0;

	virtual float getSize() const = 0;
	virtual void setSize(float size) = 0;

	virtual void streamIn() = 0;
	virtual void streamOut() = 0;
};
