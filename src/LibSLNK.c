#include "LibSLNK.h"

#include <stdlib.h>

#include "LnkBuilder.h"
#include "LinkFlags.h"



struct MSShellLink *LnkInit(void)
{
	struct MSShellLink *Link;
	
	Link = calloc(1, sizeof(struct MSShellLink));
	if (Link == NULL) {
		return NULL;
	}

	/* Fixed Value */
	Link->ShellLinkHeader.HeaderSize = 0x0000004C;

	/* Fixed Value */
	Link->ShellLinkHeader.LinkCLSID[0] = 0x01;
	Link->ShellLinkHeader.LinkCLSID[1] = 0x14;
	Link->ShellLinkHeader.LinkCLSID[2] = 0x02;
	Link->ShellLinkHeader.LinkCLSID[3] = 0x00;

	Link->ShellLinkHeader.LinkCLSID[4] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[5] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[6] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[7] = 0x00;

	Link->ShellLinkHeader.LinkCLSID[8] = 0xC0;
	Link->ShellLinkHeader.LinkCLSID[9] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[10] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[11] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[12] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[13] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[14] = 0x00;
	Link->ShellLinkHeader.LinkCLSID[15] = 0x46;

	/* Either 1, 3 or 7 */
	Link->ShellLinkHeader.ShowCommand = 0x00000001;
	LnkSetFlag(Link, LNK_FLAG_IS_UNICODE);

	return Link;
}



/* Build Link procedure */
int LnkBuild(struct MSShellLink *Link, FILE *File)
{
	if (!BuildShellLinkHeaderToFile(Link, File)) {
		return 0;
	}

	if (!BuildLinkTargetIDListToFile(Link, File)) {
		return 0;
	}

	if (!BuildStringDataToFile(Link, File)) {
		return 0;
	}

	if (!BuildExtraDataToFile(Link, File)) {
		return 0;
	}

	return 1;
}


/* Free dynamically allocated fields */
int LnkFree(struct MSShellLink *Link)
{
	/* Free IDList structure */
	if (LnkCheckFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST) && Link->LinkTargetIDList.IDList != NULL) {
		free(Link->LinkTargetIDList.IDList);
	}

	/* Free StringData structures */
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
