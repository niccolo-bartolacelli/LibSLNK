#define _CRT_SECURE_NO_WARNINGS

#include "../src/LibSLNK.h"

int test_link_to_link(void)
{
	struct MSShellLink *lnk;
	FILE *fptr;

	/* Initialization */
	lnk = LnkInit();


	/* Build a link to have the placeholder */
	fptr = _wfopen(L"C:\\Users\\~USERNAME~\\Desktop\\link_to_link.lnk", L"wb");
	LnkBuild(lnk, fptr);	/* Build empty link to provide valid link target */
	fclose(fptr);


	/* Configuration */
	LnkSetPath(lnk, L"C:\\Users\\~USERNAME~\\Desktop\\link_to_link.lnk");	/* Create Link to Link */
	LnkSetFlag(lnk, LNK_FLAG_ALLOW_LINK_TO_LINK);


	/* Build and cleanup */
	fptr = _wfopen(L"C:\\Users\\~USERNAME~\\Desktop\\link_to_link.lnk", L"wb");
	LnkBuild(lnk, fptr);
	fclose(fptr);

	LnkFree(lnk);

	return 0;
}
