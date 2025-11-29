#include "LinkFlags.h"

int LnkSetFlag(struct MSShellLink *lnk, uint32_t flag)
{
	if (lnk == NULL) return 0;

	// Set flag
	lnk->ShellLinkHeader.LinkFlags |= flag;
	
	return 1;
}

int LnkClearFlag(struct MSShellLink *lnk, uint32_t flag)
{
	if (lnk == NULL) return 0;
	
	// Clear flag
	lnk->ShellLinkHeader.LinkFlags &= ~flag;
	
	return 1;
}

int LnkCheckFlag(struct MSShellLink *lnk, uint32_t flag)
{
	if (lnk == NULL) return 0;
	
	// Check flag
	return lnk->ShellLinkHeader.LinkFlags & flag;
}
