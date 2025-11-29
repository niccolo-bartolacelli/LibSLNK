# LibSLNK - v. 0.1

Low level library to access Microsoft Shell Link file format.
The library provides the MSShellLink structure to hold any information
about the link processed.

Other structures are defined and can be used to directly access .lnk
file data. However, in an ordinary context, MSShellLink struct 
and its sub-structures SHOULD NOT be used in a direct way.
Instead, it is preferable to use MSShellLink just for declaration
and rely on the functions provided by this library to access and edit
file content.

Basic usage of the library is condensed in three steps:
  
  1. Link initialization,  
    
  2. Link configuration, and  
    
  3. Link build and cleanup.  
  
A basic program which creates a link to the file "C:\test\a.txt" is
listed below:


```
#include "LibSLNK.h"

int main(void)
{
	// Link initialization
	struct MSShellLink lnk;
	LnkInit(&lnk);

	// Link configuration
	LnkSetPath(&lnk, L"C:\\test\\a.txt");
	LnkSetString(&lnk, L"a.txt - Text File linked with LibSLNK", LNK_SD_NAME_STRING);

	// Link cleanup and build
	LnkBuild(&lnk, L"C:\\Users\\nicco\\desktop\\buildlink.lnk");
	LnkFree(&lnk);

	return 0;
}
```

  
  
**[!] ATTENTION [!]  
BE VERY CAREFUL WHEN USING CERTAIN CONFIGURATIONS, AS IT CAN RESULT IN UNEXPECTED OR
POTENTIALLY DANGEROUS BEHAVIOUR.**

Example: if you have already created an .lnk file as "C:\test\example.lnk"
and you try to create that file again, pointing to itself (i.e. `LnkSetPath(&lnk, "C:\test\example.lnk")`),
with ALLOW_LINK_TO_LINK flags set, it can result in a system crash.
