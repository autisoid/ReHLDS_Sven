#include "precompiled.h"

#include "iserverdll.h"

IServerDLL* g_pServerDLL = NULL;

/*
====================
SV_EndFrame

Physics have been integrated, notify the game dll the current frame has ended
====================
*/
void SV_EndFrame(void)
{
#if defined(REHLDS_FIXES) && defined(REHLDS_SVEN)
	GameBanDelayedCommand_t* pCommand;
	GameBanDelayedCommand_t* pTemp;
#endif // defined(REHLDS_FIXES) and defined(REHLDS_SVEN)

	if (g_pServerDLL)
		g_pServerDLL->EndFrame();

#if defined(REHLDS_FIXES) && defined(REHLDS_SVEN)
	// clean up or execute the delayed game ban commands here

	pCommand = g_pGameBanDelayedCommandHead;

	while (pCommand)
	{
		if (pCommand->m_dblTimeUntilExecution <= realtime)
		{
			Con_Printf("%s: kick command for player id %d has expired, executing it\n", __func__, pCommand->m_nUserID);

			if (pCommand->m_pszCommand)
			{
				Cbuf_AddText(pCommand->m_pszCommand);
				Mem_Free(pCommand->m_pszCommand);
				pCommand->m_pszCommand = NULL;
			}
			else
			{
				Con_Printf("%s: WARNING: empty command string for player id %d!\n", __func__, pCommand->m_nUserID);
			}

			pTemp = pCommand;
			pCommand = pTemp->m_pNext;

			// update list pointers first, then free to avoid use-after-free
			if (pTemp == g_pGameBanDelayedCommandHead)
			{
				g_pGameBanDelayedCommandHead = pCommand;
				if (g_pGameBanDelayedCommandHead)
				{
					g_pGameBanDelayedCommandHead->m_pPrev = NULL;
				}
				else
				{
					g_pGameBanDelayedCommandTail = NULL;
				}
			}
			else if (pTemp == g_pGameBanDelayedCommandTail)
			{
				g_pGameBanDelayedCommandTail = pTemp->m_pPrev;
				if (g_pGameBanDelayedCommandTail)
				{
					g_pGameBanDelayedCommandTail->m_pNext = NULL;
				}
				else
				{
					g_pGameBanDelayedCommandHead = NULL;
				}
			}
			else
			{
				if (pTemp->m_pPrev)
				{
					pTemp->m_pPrev->m_pNext = pTemp->m_pNext;
				}
				if (pTemp->m_pNext)
				{
					pTemp->m_pNext->m_pPrev = pTemp->m_pPrev;
				}
			}

			Mem_Free(pTemp);
			continue;
		}

		pCommand = pCommand->m_pNext;
	}
#endif // defined(REHLDS_FIXES) and defined(REHLDS_SVEN)
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
