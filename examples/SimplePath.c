#include "LibSLNK.h"

int main(void)
{
	/* Initialization */
	struct MSShellLink lnk;
	LnkInit(&lnk);


	/* Configuration */
	LnkSetPath(&lnk, L"C:\\test\\a.txt");


	/* Build and cleanup */
	LnkBuild(&lnk, L"C:\\test\\lnk_to_a.txt.lnk");
	LnkFree(&lnk);

	return 0;
}
