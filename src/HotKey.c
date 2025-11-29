#include "HotKey.h"

int SetHotKey(struct MSShellLink *lnk, uint8_t modifier, uint8_t vkey)
{
	if (lnk == NULL) return 0;

	// Set HotKey
	lnk->ShellLinkHeader.HotKey = 0x0000;
	lnk->ShellLinkHeader.HotKey |= vkey;
	lnk->ShellLinkHeader.HotKey |= modifier << 8;

	return 1;
}

int ClearHotKey(struct MSShellLink *lnk)
{
	if (lnk == NULL) return 0;
	
	// Set HotKey to NONE
	lnk->ShellLinkHeader.HotKey = 0x0000;
	
	return 0;
}
