#include "precompiled.h"

#include "engineserver.h"

CEngineServer g_EngineServer;

unsigned char* CEngineServer::AddPositionToFatPVS(float* org) {
	return SV_AddPositionToFatPVS(org);
}

unsigned char* CEngineServer::AddPositionToFatPAS(float* org) {
	return SV_AddPositionToFatPAS(org);
}

int CEngineServer::NumberOfPrecachedModels(void) {
	return PF_NumberOfPrecachedModels();
}

void* CEngineServer::GetModelPtrByIndex(int index) {
	return Mod_Extradata(Mod_Handle(index)); //GetModelPtrByIndex(index);
}

const char* CEngineServer::GetAddressOfPlayer(edict_t* _Edict, int _Unnamed) {
	int			i;
	client_t*	pcl;
	client_t*	pneeded;

	if (!g_psv.active)
		return NULL;
	if (!_Edict)
		return NULL;
	if (g_psvs.maxclients <= 0)
		return NULL;

	pneeded = NULL;

	for (i = 0, pcl = g_psvs.clients; i < g_psvs.maxclients; i++, pcl++) {
		if (pcl->edict == _Edict) {
			pneeded = pcl;
			break;
		}
	}

	if (!pneeded)
		return NULL;

	if (pneeded->fakeclient)
		return "bot";

	return NET_AdrToString(pneeded->netchan.remote_address);
}

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CEngineServer, IEngineServer, IENGINESERVER_INTERFACE_VERSION, g_EngineServer);
