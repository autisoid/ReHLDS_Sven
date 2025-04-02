#include "precompiled.h"

#include "iserverdll.h"

IServerDLL* g_pServerDLL = NULL;

/*
====================
SV_EndFrame

Physics have been integrated, notify the game dll the current frame has ended
====================
*/
void SV_EndFrame( void )
{
	if (g_pServerDLL)
		g_pServerDLL->EndFrame();
}

/*
====================
SV_NotifyClients

Send a message to all clients
====================
*/
void SV_NotifyClients( const char* _Text )
{
	if (g_pServerDLL)
		g_pServerDLL->NotifyClients(_Text);
}

/*
====================
SV_OnLevelChange

Notifies the game dll about a level change
====================
*/
void SV_OnLevelChange( const char *_MapName )
{
	if (g_pServerDLL)
		g_pServerDLL->OnChangeLevel(_MapName);
}
