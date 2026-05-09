#include "HotKey.h"

uint16_t GetHotKey(struct MSShellLink *Link)
{
	if (Link == NULL) return 0;

	/* Get HotKey */
	return Link->ShellLinkHeader.HotKey;
}

int SetHotKey(struct MSShellLink *Link, uint8_t Modifier, uint8_t VKey)
{
	if (Link == NULL) return 0;

	/* Set HotKey */
	Link->ShellLinkHeader.HotKey = 0x0000;
	Link->ShellLinkHeader.HotKey |= VKey;
	Link->ShellLinkHeader.HotKey |= Modifier << 8;

	return 1;
}

int ClearHotKey(struct MSShellLink *Link)
{
	if (Link == NULL) return 0;
	
	/* Set HotKey to NONE */
	Link->ShellLinkHeader.HotKey = 0x0000;
	
	return 0;
}
