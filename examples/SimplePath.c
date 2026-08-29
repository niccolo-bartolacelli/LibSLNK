#define _CRT_SECURE_NO_WARNINGS

#include "../src/LibSLNK.h"

int test_simple_path(void)
{
	struct MSShellLink *lnk;
	FILE *fptr;

	/* Initialization */
	lnk = LnkInit();


	/* Configuration */
	LnkSetPath(lnk, L"C:\\test\\a.txt");


	/* Build and cleanup */
	fptr = _wfopen(L"C:\\test\\lnk_to_a.txt.lnk", L"wb");
	LnkBuild(lnk, fptr);
	fclose(fptr);

	LnkFree(lnk);

	return 0;
}
