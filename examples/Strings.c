#include "LibSLNK.h"

int main(void)
{
	/* Initialization */
	struct MSShellLink lnk;
	LnkInit(&lnk);


	/* Configuration */
	LnkSetPath(&lnk, L"C:\\Windows\\System32\\cmd.exe");

	LnkSetString(&lnk, L"/c start calc", LNK_SD_COMMAND_LINE_ARGUMENTS);
	LnkSetString(&lnk, L"Click Me!", LNK_SD_NAME_STRING);


	/* Build and cleanup */
	LnkBuild(&lnk, L"C:\\test\\lnk_to_a.txt.lnk");
	LnkFree(&lnk);

	return 0;
}
