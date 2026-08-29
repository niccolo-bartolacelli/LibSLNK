#define _CRT_SECURE_NO_WARNINGS

#include "../src/LibSLNK.h"

int test_file_times(void)
{
	struct MSShellLink *lnk;
	FILE *fptr;

	/* Initialization */
	lnk = LnkInit();


	/* Configuration */
	LnkSetPath(lnk, L"C:\\test\\al.txt");

	SYSTEMTIME time = { 0 };

	time.wYear = 2023;
	time.wMonth = 4;
	time.wDay = 13;
	time.wHour = 12;
	time.wMinute = 23;
	time.wSecond = 0;
	time.wMilliseconds = 0;

	LnkSetAccessTime(lnk, &time);


	/* Build and cleanup */
	fptr = _wfopen(L"C:\\test\\Start Calc.lnk", L"wb");
	LnkBuild(lnk, fptr);
	fclose(fptr);

	LnkFree(lnk);

	return 0;
}
