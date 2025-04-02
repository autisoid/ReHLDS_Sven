#pragma once

#include "iengineserver.h"

class CEngineServer : public IEngineServer
{
public:
	unsigned char* AddPositionToFatPVS(float* org) override;
	unsigned char* AddPositionToFatPAS(float* org) override;
	int NumberOfPrecachedModels(void) override;
	void* GetModelPtrByIndex(int index) override;
	const char* GetAddressOfPlayer(edict_t* _Edict, int _Unnamed) override;
};

extern CEngineServer g_EngineServer;
