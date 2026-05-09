#include "FileAttributes.h"

#include "LinkFlags.h"

int LnkCheckFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute)
{
	if (Link == NULL) {
		return 0;
	}

	/* Check attribute */
	return Link->ShellLinkHeader.FileAttributes & FileAttribute;
}

int LnkSetFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute)
{
	if (Link == NULL) {
		return 0;
	}
	
	/* Set attribute */
	Link->ShellLinkHeader.FileAttributes |= FileAttribute;

	/* Clear reserved bits */
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED_1;
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED_2;

	return 1;
}

int LnkClearFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute)
{
	if (Link == NULL) {
		return 0;
	}

	/* Clear attribute */
	Link->ShellLinkHeader.FileAttributes &= ~FileAttribute;

	/* Clear reserved bits */
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED_1;
	Link->ShellLinkHeader.FileAttributes &= ~LNK_FILE_ATTRIBUTE_RESERVED_2;

	return 1;
}
