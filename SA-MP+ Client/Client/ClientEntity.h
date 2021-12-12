#pragma once

#include "ClientEntityBase.h"

enum eClientEntityClassTypes
{
	CLASS_ClientEntity,
	CLASS_ClientMarker,
	CLASS_ClientStreamElement
};

enum eClientEntityType
{
	CLIENTMARKER
};

class ClientManager;

class ClientEntity : public ClientEntityBase
{
	DECLARE_BASE_CLASS(ClientEntity)
protected:
	ClientManager* manager;
	int id;
	bool local;

public:
	ClientEntity(int id, bool local);
	virtual ~ClientEntity();

	virtual eClientEntityType getType() const = 0;
	bool isLocalEntity() { return local; }

	virtual void unlink() = 0;

	int getID() { return id; }
	void setID(int id);

	virtual bool getMatrix(CMatrix& matrix) const;
	virtual bool setMatrix(const CMatrix& matrix);

	virtual void getPosition(CVector& position) const = 0;
	virtual void setPosition(const CVector& position) = 0;

	virtual void getRotationRadians(CVector& outRadians) const;
	virtual void setRotationRadians(const CVector& radians);

	virtual CEntity* getGameEntity() { return NULL; }
	virtual const CEntity* getGameEntity() const { return NULL; }

	bool isDoubleSided();
	void setDoubleSided(bool enable);

	virtual CSphere getWorldBoundingSphere();
	
	float getDistanceBetweenBoundingSpheres(ClientEntity* other);
};
