#pragma once

class MarkerManager;
class PacketTranslator;
class RPCFunctions;

class SendList : public std::list<Player*>
{
public:
	void push_back(Player* player) { this->push_back(player); }
};

class Game
{
private:
	float gameSpeed;
	float aircraftMaxHeight;

	unsigned char skyGradientTR, skyGradientTG, skyGradientTB;
	unsigned char skyGradientBR, skyGradientBG, skyGradientBB;
	bool skyGradientHas;

	SHeatHazeSettings heatHazeSettings;
	bool heatHazeHas;

	bool overrideWaterColor;
	unsigned char waterRed, waterGreen, waterBlue, waterAlpha;

	bool interiorSoundsEnabled;

	bool overrideRainLevel;
	float rainLevel;

	bool overrideSunSize;
	float sunSize;

	bool overrideMoonSize;
	int moonSize;

	bool overrideSunColor;
	unsigned char sunCoreR, sunCoreG, sunCoreB, sunCoronaR, sunCoronaG, sunCoronaB;

	bool overrideWindVelocity;
	float windVelX, windVelY, windVelZ;

	bool overrideFarClip;
	float farClipDistance;

	bool overrideFogDistance;
	float fogDistance;

	bool cloudsEnabled;

	bool serverFullyUp;

	MarkerManager* markerManager;
	RPCFunctions* rpcFunctions;
	PacketTranslator* packetTranslator;
	PlayerManager* playerManager;

public:
	Game();
	~Game();

	float getGameSpeed() { return gameSpeed; }
	void setGameSpeed(float gameSpeed) { this->gameSpeed = gameSpeed; }

	bool hasSkyGradient() { return skyGradientHas; }
	void setHasSkyGradient(bool skyGradientHas) { this->skyGradientHas = skyGradientHas; }

	void getSkyGradient(unsigned char& tr, unsigned char& tg, unsigned char& tb, unsigned char& br, unsigned char& bg, unsigned char& bb)
	{
		tr = skyGradientTR;
		tg = skyGradientTG;
		tb = skyGradientTB;
		br = skyGradientBR;
		bg = skyGradientBG;
		bb = skyGradientBB;
	}

	void setSkyGradient(unsigned char& tr, unsigned char& tg, unsigned char& tb, unsigned char& br, unsigned char& bg, unsigned char& bb)
	{
		skyGradientTR = tr;
		skyGradientTG = tg;
		skyGradientTB = tb;
		skyGradientBR = br;
		skyGradientBG = bg;
		skyGradientBB = bb;
	}

	bool hasHeatHaze() { return heatHazeHas; }
	void setHasHeatHaze(bool heatHazeHas) { this->heatHazeHas = heatHazeHas; }

	void getHeatHaze(SHeatHazeSettings& heatHazeSettings) { heatHazeSettings = this->heatHazeSettings; }
	void setHeatHaze(const SHeatHazeSettings& heatHazeSettings) { this->heatHazeSettings = heatHazeSettings; }

	bool getInteriorSoundsEnabled() { return interiorSoundsEnabled; }
	void setInteriorSoundsEnabled(bool enable) { interiorSoundsEnabled = enable; }

	bool hasWaterColor() { return overrideWaterColor; }
	void setHasWaterColor(bool overrideWaterColor) { this->overrideWaterColor = overrideWaterColor; }

	void getWaterColor(unsigned char& red, unsigned char& green, unsigned char& blue, unsigned char& alpha)
	{
		red = waterRed;
		green = waterGreen;
		blue = waterBlue;
		alpha = waterAlpha;
	}

	void setSkyGradient(unsigned char& red, unsigned char& green, unsigned char& blue, unsigned char& alpha)
	{
		waterRed = red;
		waterGreen = green;
		waterBlue = blue;
		waterAlpha = alpha;
	}

	bool hasRainLevel() { return overrideRainLevel; }
	void setHasRainLevel(bool overrideRainLevel) { this->overrideRainLevel = overrideRainLevel; }

	float getRainLevel() { return rainLevel; }
	void setRainLevel(float& rainLevel) { this->rainLevel = rainLevel; }

	bool hasSunSize() { return overrideSunSize; }
	void setHasSunSize(bool overrideSunSize) { this->overrideSunSize = overrideSunSize; }

	float getSunSize() { return sunSize; }
	void setSunSize(float& sunSize) { this->sunSize = sunSize; }

	bool hasSunColor() { return overrideSunColor; }
	void setHasSunColor(bool overrideSunColor) { this->overrideSunColor = overrideSunColor; }

	float getSunColor(unsigned char& coreR, unsigned char& coreG, unsigned char& coreB, unsigned char& coronaR, unsigned char& coronaG,
		unsigned char& coronaB)
	{
		coreR = sunCoreR;
		coreG = sunCoreG;
		coreB = sunCoreB;
		coronaR = sunCoronaR;
		coronaG = sunCoronaG;
		coronaB = sunCoronaB;
	}
	float setSunColor(unsigned char& coreR, unsigned char& coreG, unsigned char& coreB, unsigned char& coronaR, unsigned char& coronaG,
		unsigned char& coronaB)
	{
		sunCoreR = coreR;
		sunCoreG = coreG;
		sunCoreB = coreB;
		sunCoronaR = coronaR;
		sunCoronaG = coronaG;
		sunCoronaB = coronaB;
	}

	bool hasWindVelocity() { return overrideWindVelocity; }
	void setHasWindVelocity(bool overrideWindVelocity) { this->overrideWindVelocity = overrideWindVelocity; }

	void getWindVelocity(float& fVelX, float& fVelY, float& fVelZ)
	{
		fVelX = windVelX;
		fVelY = windVelY;
		fVelZ = windVelZ;
	}
	void setWindVelocity(float& fVelX, float& fVelY, float& fVelZ)
	{
		windVelX = fVelX;
		windVelY = fVelY;
		windVelZ = fVelZ;
	}

	bool hasFarClipDistance() { return overrideFarClip; }
	void setHasFarClipDistance(bool overrideFarClip) { this->overrideFarClip = overrideFarClip; }

	float getFarClipDistance() { return farClipDistance; }
	void setFarClipDistance(float& farClipDistance) { this->farClipDistance = farClipDistance; }

	bool hasFogDistance() { return overrideFogDistance; }
	void setHasFogDistance(bool overrideFogDistance) { this->overrideFogDistance = overrideFogDistance; }

	float getFogDistance() { return fogDistance; }
	void setFogDistance(float& fogDistance) { this->fogDistance = fogDistance; }

	float getAircraftMaxHeight() { return aircraftMaxHeight; }
	void setAircraftMaxHeight(float maxHeight) { aircraftMaxHeight = maxHeight; }

	void resetMapInfo();

	void setCloudsEnabled(bool enabled);
	void getCloudsEnabled();

	bool hasMoonSize() { return overrideMoonSize; }
	void setHasMoonSize(bool overrideMoonSize) { this->overrideMoonSize = overrideMoonSize; }

	int getMoonSize() { return moonSize; }
	void setMoonSize(int moonSize) { this->moonSize = moonSize; }

	void start();
	void doPulse();

	static bool staticPacketHandler(unsigned short packetID, RakNet::SystemAddress address, RakNet::BitStream& bitStream, int extra);
	bool processPacket(Packet& packet);

	bool sendPacket(unsigned char packetID, const RakNet::SystemAddress& playerSocket, RakNet::BitStream* bitStream, bool broadCast,
		PacketPriority packetPriority, PacketReliability packetReliability, char packetOrdering = DEFAULT_ORDERING_CHANNEL);

	void packet_PlayerJoinData(PlayerJoinDataPacket& packet);
};
