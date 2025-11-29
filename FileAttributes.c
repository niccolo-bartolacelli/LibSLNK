#include "FileAttributes.h"

#include "LinkFlags.h"

int SetFileAttribute(struct MSShellLink *Link, uint32_t Flag)
{
	if (Link == NULL) return 0;
	
	// Set flag
	Link->ShellLinkHeader.FileAttributes |= Flag;

	// Clear reserved flags
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED1;
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED2;

	return 1;
}

int ClearFileAttribute(struct MSShellLink *Link, uint32_t Flag)
{
	if (Link == NULL) return 0;

	// Clear flag
	Link->ShellLinkHeader.FileAttributes &= ~Flag;

	// Clear reserved flags
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED1;
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED2;

	return 1;
}
