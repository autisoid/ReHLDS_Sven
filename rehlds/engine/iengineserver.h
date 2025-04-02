#pragma once

#include "interface.h"

class IEngineServer : public IBaseInterface
{
public:
	virtual ~IEngineServer() {}

	virtual unsigned char* AddPositionToFatPVS(float* org) = 0;
	virtual unsigned char* AddPositionToFatPAS(float* org) = 0;
	virtual int NumberOfPrecachedModels(void) = 0;
	virtual void* GetModelPtrByIndex(int index) = 0;
	virtual const char* GetAddressOfPlayer(edict_t* _Edict, int _Unnamed) = 0;
};

#define IENGINESERVER_INTERFACE_VERSION "SCEngineServer002"

































