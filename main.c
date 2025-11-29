#include "LibSLNK.h"

int main(void)
{
	/* Initialization */
	struct MSShellLink lnk;
	LnkInit(&lnk);


	/* Configuration */
	LnkSetPath(&lnk, L"C:\\Users\\nicco\\desktop\\buildlink.lnk");
	LnkSetFlag(&lnk, LNK_FLAG_ALLOW_LINK_TO_LINK);
	


	/* Build and cleanup */
	LnkBuild(&lnk, L"C:\\Users\\nicco\\desktop\\buildlink.lnk");
	LnkFree(&lnk);

	return 0;
}
