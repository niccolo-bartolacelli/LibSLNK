#include "../LibSLNK/src/LibSLNK.h"

int main(void)
{
	struct MSShellLink *Link;
	
	/* Initialization */
	Link = LnkInit();

	/* Configuration */
	LnkSetPath(Link, L"C:\\Users\\nicco\\Desktop\\pic.JPG");

	/* Build and free */
	LnkBuild(Link, L"C:\\Users\\nicco\\desktop\\immagine.lnk");
	LnkFree(Link);

	return 0;
}
