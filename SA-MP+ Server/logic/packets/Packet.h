#pragma once

enum
{
	PACKET_RELIABLE = 1,
	PACKET_SEQUENCED = 2,
	PACKET_HIGH_PRIORITY = 4,
	PACKET_LOW_PRIORITY = 8,

	PACKET_UNRELIABLE = 0,
	PACKET_MEDIUM_PRIORITY = 0
};

class Packet
{
protected:
	Element* sourceElement;
	RakNet::SystemAddress source;

public:
	Packet();
	virtual ~Packet() {};

	virtual bool requiresSourcePlayer() const { return true; }
	virtual ePacketType getPacketID() const = 0;
	virtual char getPacketOrdering() const { return DEFAULT_ORDERING_CHANNEL; }
	virtual unsigned long getFlags() const = 0;

	virtual bool read(RakNet::BitStream& bitStream) { return false; }
	virtual bool write(RakNet::BitStream& bitStream) const { return false; }

	void setSourceElement(Element* source) { sourceElement = source; }
	Element* getSourceElement() const { return sourceElement; }
	Player* getSourcePlayer();
	void setSourceSocket(const RakNet::SystemAddress& source) { this->source = source; }
	const RakNet::SystemAddress& getSourceSocket() const { return source; }
	unsigned long getSourceIP() const { return source.address.addr4.sin_addr.S_un.S_addr; }
	unsigned short getSourcePort() const { return source.GetPort(); }
};