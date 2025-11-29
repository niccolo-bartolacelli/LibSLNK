#include <wchar.h>
#include "LnkBuilder.h"
#include "LinkFlags.h"

// ATTENTION!! THIS MACRO IS SOLELY INTENTED TO BE USED IN FILE WRITE PROCESS AND SHOULD NOT BE USED IN ANY OTHER CONTEXT. BE CAREFUL USING IT
#define WRITES(x, fptr) fwrite_le(&(x), sizeof(x), fptr);


// Helper function
void fwrite_le(const void *buffer, size_t buff_size, FILE *fptr)
{
	uint8_t *tmp = (uint8_t *)buffer;

	for (size_t i = 0; i < buff_size; i++) {
		fwrite(tmp, 1, 1, fptr);
		tmp++;
	}
}



// Main functions
int BuildShellLinkHeaderToFile(struct MSShellLink *lnk, FILE *fptr)
{
	if (lnk == NULL) return 0;

	WRITES(lnk->ShellLinkHeader.HeaderSize, fptr);
	WRITES(lnk->ShellLinkHeader.LinkCLSID1, fptr);
	WRITES(lnk->ShellLinkHeader.LinkCLSID2, fptr);
	WRITES(lnk->ShellLinkHeader.LinkCLSID3, fptr);
	WRITES(lnk->ShellLinkHeader.LinkFlags, fptr);
	WRITES(lnk->ShellLinkHeader.FileAttributes, fptr);
	WRITES(lnk->ShellLinkHeader.CreationTime, fptr);
	WRITES(lnk->ShellLinkHeader.AccessTime, fptr);
	WRITES(lnk->ShellLinkHeader.WriteTime, fptr);
	WRITES(lnk->ShellLinkHeader.FileSize, fptr);
	WRITES(lnk->ShellLinkHeader.IconIndex, fptr);
	WRITES(lnk->ShellLinkHeader.ShowCommand, fptr);
	WRITES(lnk->ShellLinkHeader.HotKey, fptr);
	WRITES(lnk->ShellLinkHeader.Reserved1, fptr);
	WRITES(lnk->ShellLinkHeader.Reserved2, fptr);
	WRITES(lnk->ShellLinkHeader.Reserved3, fptr);

	return 1;
}

int BuildLinkTargetIDListToFile(struct MSShellLink *lnk, FILE *fptr)
{
	if (lnk == NULL) return 0;

	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_TARGET_IDLIST)) {
		WRITES(lnk->LinkTargetIDList.IDListSize, fptr);

		for (uint16_t i = 0; i < lnk->LinkTargetIDList.IDListSize; i++) {
			WRITES(lnk->LinkTargetIDList.IDList[i], fptr);
		}

		//WRITES(lnk->LinkTargetIDList.TerminalID, fptr);
	}

	return 1;
}

int BuildStringDataToFile(struct MSShellLink *lnk, FILE *fptr)
{
	if (lnk == NULL) return 0;
	
	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_NAME)) {
		WRITES(lnk->StringData.NameString.CountCharacters, fptr);

		for (uint16_t i = 0; i < lnk->StringData.NameString.CountCharacters; i++) {
			WRITES(lnk->StringData.NameString.String[i], fptr);
		}
	}

	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_RELATIVE_PATH)) {
		WRITES(lnk->StringData.RelativePath.CountCharacters, fptr);

		for (uint16_t i = 0; i < lnk->StringData.RelativePath.CountCharacters; i++) {
			WRITES(lnk->StringData.RelativePath.String[i], fptr);
		}
	}

	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_WORKING_DIR)) {
		WRITES(lnk->StringData.WorkingDir.CountCharacters, fptr);

		for (uint16_t i = 0; i < lnk->StringData.WorkingDir.CountCharacters; i++) {
			WRITES(lnk->StringData.WorkingDir.String[i], fptr);
		}
	}

	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_ARGUMENTS)) {
		WRITES(lnk->StringData.CommandLineArguments.CountCharacters, fptr);

		for (uint16_t i = 0; i < lnk->StringData.CommandLineArguments.CountCharacters; i++) {
			WRITES(lnk->StringData.CommandLineArguments.String[i], fptr);
		}
	}

	if (LnkCheckFlag(lnk, LNK_FLAG_HAS_ICON_LOCATION)) {
		WRITES(lnk->StringData.IconLocation.CountCharacters, fptr);

		for (uint16_t i = 0; i < lnk->StringData.IconLocation.CountCharacters; i++) {
			WRITES(lnk->StringData.IconLocation.String[i], fptr);
		}
	}
	
	return 1;
}
