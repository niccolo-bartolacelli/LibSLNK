#include <stdio.h>
#include <stdlib.h>

#include "LibSLNK.h"
#include "LnkBuilder.h"
#include "LinkFlags.h"



int LnkInit(struct MSShellLink *Link)
{
	// Fixed Value
	Link->ShellLinkHeader.HeaderSize = 0x0000004C;

	// Fixed Value
	Link->ShellLinkHeader.LinkCLSID1 = 0x00021401;
	Link->ShellLinkHeader.LinkCLSID2 = 0x00000000;
	Link->ShellLinkHeader.LinkCLSID3 = 0x46000000000000C0;

	// Initialize on 0, can be set later
	Link->ShellLinkHeader.LinkFlags = 0x00000000;
	LnkSetFlag(Link, LNK_FLAG_IS_UNICODE);					 // Sets default to UNICODE, ANSI not supported

	Link->ShellLinkHeader.FileAttributes = 0x00000000;

	Link->ShellLinkHeader.CreationTime = 0x0000000000000000;
	Link->ShellLinkHeader.AccessTime = 0x0000000000000000;
	Link->ShellLinkHeader.WriteTime = 0x0000000000000000;

	Link->ShellLinkHeader.FileSize = 0x00000000;
	Link->ShellLinkHeader.IconIndex = 0x00000000;
	Link->ShellLinkHeader.ShowCommand = 0x00000001;

	Link->ShellLinkHeader.HotKey = 0x0000;

	// Fixed values
	Link->ShellLinkHeader.Reserved1 = 0x0000;
	Link->ShellLinkHeader.Reserved2 = 0x00000000;
	Link->ShellLinkHeader.Reserved3 = 0x00000000;


	// IDList
	Link->LinkTargetIDList.IDListSize = 0x0000;
	Link->LinkTargetIDList.IDList = NULL;
	Link->LinkTargetIDList.TerminalID = 0x0000;


	//LinkInfo
	Link->LinkInfo.LinkInfoSize = 0;

	// StringData
	Link->StringData.NameString.CountCharacters = 0x0000;
	Link->StringData.RelativePath.CountCharacters = 0x0000;
	Link->StringData.WorkingDir.CountCharacters = 0x0000;
	Link->StringData.CommandLineArguments.CountCharacters = 0x0000;
	Link->StringData.IconLocation.CountCharacters = 0x0000;

	Link->StringData.NameString.String = NULL;
	Link->StringData.RelativePath.String = NULL;
	Link->StringData.WorkingDir.String = NULL;
	Link->StringData.CommandLineArguments.String = NULL;
	Link->StringData.IconLocation.String = NULL;


	// ExtraData
	Link->ExtraData.TerminalBlock = 0x00000000;


	return 1;
}



// Build Link procedure
int LnkBuild(struct MSShellLink *Link, const wchar_t *Path)
{
	FILE *fptr = _wfopen(Path, L"wb");
	if (fptr == 0) return 0;

	BuildShellLinkHeaderToFile(Link, fptr);
	BuildLinkTargetIDListToFile(Link, fptr);
	BuildStringDataToFile(Link, fptr);

	fclose(fptr);

	return 1;
}


// Free dynamically allocated fields
int LnkFree(struct MSShellLink *Link)
{
	// Free IDList structure
	if (LnkCheckFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST) && Link->LinkTargetIDList.IDList != NULL) {
		free(Link->LinkTargetIDList.IDList);
	}

	// Free StringData structures
	if (LnkCheckFlag(Link, LNK_FLAG_HAS_NAME) && Link->StringData.NameString.String != NULL) {
		free(Link->StringData.NameString.String);
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_RELATIVE_PATH) && Link->StringData.RelativePath.String != NULL) {
		free(Link->StringData.RelativePath.String);
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_WORKING_DIR) && Link->StringData.WorkingDir.String != NULL) {
		free(Link->StringData.WorkingDir.String);
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_ARGUMENTS) && Link->StringData.CommandLineArguments.String != NULL) {
		free(Link->StringData.CommandLineArguments.String);
	}

	if (LnkCheckFlag(Link, LNK_FLAG_HAS_ICON_LOCATION) && Link->StringData.IconLocation.String != NULL) {
		free(Link->StringData.IconLocation.String);
	}

	return 1;
}
