#include <wchar.h>
#include "LnkBuilder.h"
#include "LinkFlags.h"

/* ATTENTION!! THIS MACRO IS SOLELY INTENTED TO BE USED IN FILE WRITE PROCESS AND SHOULD NOT BE USED IN ANY OTHER CONTEXT. BE CAREFUL USING IT */
#define WRITES(x, fptr) fwrite_le(&(x), sizeof(x), fptr);

/* Handle different implementation based on architecture */
void fwrite_le(const void *buffer, size_t buff_size, FILE *fptr)
{
	uint8_t *tmp;
	size_t i;

#ifdef _BIG_ENDIAN
	tmp = ((uint8_t *)buffer) + (buff_size - 1);

	for (i = buffsize - 1; i --> 0;) {
		fputc(*tmp, fptr);
		tmp--;
	}
#else
	tmp = (uint8_t *)buffer;

	for (i = 0; i < buff_size; i++) {
		fputc(*tmp, fptr);
		tmp++;
	}
#endif
}



// Main functions
int BuildShellLinkHeaderToFile(struct MSShellLink *Link, FILE *fptr)
{
	if (Link == NULL) {
		return 0;
	}

	WRITES(Link->ShellLinkHeader.HeaderSize, fptr);
	WRITES(Link->ShellLinkHeader.LinkCLSID, fptr);
	WRITES(Link->ShellLinkHeader.LinkFlags, fptr);
	WRITES(Link->ShellLinkHeader.FileAttributes, fptr);

	WRITES(Link->ShellLinkHeader.CreationTime.dwLowDateTime, fptr);
	WRITES(Link->ShellLinkHeader.CreationTime.dwHighDateTime, fptr);
	WRITES(Link->ShellLinkHeader.AccessTime.dwLowDateTime, fptr);
	WRITES(Link->ShellLinkHeader.AccessTime.dwHighDateTime, fptr);
	WRITES(Link->ShellLinkHeader.WriteTime.dwLowDateTime, fptr);
	WRITES(Link->ShellLinkHeader.WriteTime.dwHighDateTime, fptr);

	WRITES(Link->ShellLinkHeader.FileSize, fptr);
	WRITES(Link->ShellLinkHeader.IconIndex, fptr);
	WRITES(Link->ShellLinkHeader.ShowCommand, fptr);
	WRITES(Link->ShellLinkHeader.HotKey, fptr);

	WRITES(Link->ShellLinkHeader.Reserved1, fptr);
	WRITES(Link->ShellLinkHeader.Reserved2, fptr);
	WRITES(Link->ShellLinkHeader.Reserved3, fptr);

	return 1;
}

int BuildLinkTargetIDListToFile(struct MSShellLink *Link, FILE *fptr)
{
	size_t i, j;

	if (Link == NULL) {
		return 0;
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST)) {
		WRITES(Link->LinkTargetIDList.IDListSize, fptr);

		for (i = 0; Link->LinkTargetIDList.IDList[i].ItemIDSize != 0x0000; i++) {
			WRITES(Link->LinkTargetIDList.IDList[i].ItemIDSize, fptr);

			for (j = 0; j < Link->LinkTargetIDList.IDList[i].ItemIDSize - sizeof(Link->LinkTargetIDList.IDList[i].ItemIDSize); j++) { /* Remember to subtract size field length */
				WRITES(Link->LinkTargetIDList.IDList[i].Data[j], fptr);
			}
		}

		WRITES(Link->LinkTargetIDList.IDList[i].ItemIDSize, fptr);
	}

	return 1;
}

int BuildStringDataToFile(struct MSShellLink *Link, FILE *fptr)
{
	uint16_t i;

	if (Link == NULL) {
		return 0;
	}
	
	if (LnkCheckFlag(Link, LNK_FLAG_HAS_NAME)) {
		WRITES(Link->StringData.NameString.CountCharacters, fptr);

		for (i = 0; i < Link->StringData.NameString.CountCharacters; i++) {
			WRITES(Link->StringData.NameString.StringUnicode[i], fptr);
		}
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_RELATIVE_PATH)) {
		WRITES(Link->StringData.RelativePath.CountCharacters, fptr);

		for (i = 0; i < Link->StringData.RelativePath.CountCharacters; i++) {
			WRITES(Link->StringData.RelativePath.StringUnicode[i], fptr);
		}
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_WORKING_DIR)) {
		WRITES(Link->StringData.WorkingDir.CountCharacters, fptr);

		for (i = 0; i < Link->StringData.WorkingDir.CountCharacters; i++) {
			WRITES(Link->StringData.WorkingDir.StringUnicode[i], fptr);
		}
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_ARGUMENTS)) {
		WRITES(Link->StringData.CommandLineArguments.CountCharacters, fptr);

		for (i = 0; i < Link->StringData.CommandLineArguments.CountCharacters; i++) {
			WRITES(Link->StringData.CommandLineArguments.StringUnicode[i], fptr);
		}
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_ICON_LOCATION)) {
		WRITES(Link->StringData.IconLocation.CountCharacters, fptr);

		for (i = 0; i < Link->StringData.IconLocation.CountCharacters; i++) {
			WRITES(Link->StringData.IconLocation.StringUnicode[i], fptr);
		}
	}
	
	return 1;
}

int BuildExtraDataToFile(struct MSShellLink *Link, FILE *fptr)
{
	uint32_t terminal;

	terminal = 0x00000000;
	WRITES(terminal, fptr);
	
	return 1;
}
