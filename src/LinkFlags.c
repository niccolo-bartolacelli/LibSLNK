#include "LinkFlags.h"

int LnkCheckFlag(struct MSShellLink *Link, uint32_t Flag)
{
	if (Link == NULL) {
		return 0;
	}

	/* Check flag */
	return Link->ShellLinkHeader.LinkFlags & Flag;
}

int LnkSetFlag(struct MSShellLink *Link, uint32_t Flag)
{
	if (Link == NULL) {
		return 0;
	}

	/* Set flag */
	Link->ShellLinkHeader.LinkFlags |= Flag;

	return 1;
}

int LnkClearFlag(struct MSShellLink *Link, uint32_t Flag)
{
	if (Link == NULL) {
		return 0;
	}

	/* Clear flag */
	Link->ShellLinkHeader.LinkFlags &= ~Flag;

	return 1;
}
