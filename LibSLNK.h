/**
*	LibSLNK - v. 0.1
*
*	Low level library to access Microsoft Shell Link file format.
*	The library provides the MSShellLink structure to hold any information
*	about the link processed.
*
*	Other structures are defined and can be used to directly access .lnk
*	file data. However, in an ordinary context, MSShellLink struct 
*	and its sub-structures SHOULD NOT be used in a direct way.
*	Instead, it is preferable to use MSShellLink just for declaration
*	and rely on the functions provided by this library to access and edit
*	file content.
* 
*	Basic usage of the library is condensed in three steps:
*
*		1. Link initialization,
* 
*		2. Link configuration, and
* 
*		3. Link build and cleanup.
* 
*	A basic program which creates a link to the file "C:\test\a.txt" is
*	listed below:
* 
* 
* 
*	#include "LibSLNK.h"
* 
*	int main(void)
*	{
*		// Link initialization
*		struct MSShellLink lnk;
*		LnkInit(&lnk);
* 
*		// Link configuration
*		LnkSetPath(&lnk, L"C:\\test\\a.txt");
*		LnkSetString(&lnk, L"a.txt - Text File linked with LibSLNK", LNK_SD_NAME_STRING);
*
*		// Link cleanup and build
*		LnkBuild(&lnk, L"C:\\Users\\nicco\\desktop\\buildlink.lnk");
*		LnkFree(&lnk);
*
*		return 0;
*	}
* 
* 
*
*	[!] ATTENTION [!]
*	BE VERY CAREFUL WHEN USING CERTAIN CONFIGURATIONS, AS IT CAN RESULT IN UNEXPECTED OR
*	POTENTIALLY DANGEROUS BEHAVIOUR.
*	AS AN EXAMPLE, IF YOU HAVE PREVIOUSLY CREATED AN .lnk FILE AS "C:\test\example.lnk"
*	AND YOU TRY TO CREATE THAT FILE AGAIN, POINTING TO ITSELF, WITH ALLOW_LINK_TO_LINK
*	FLAG SET, IT WILL RESULT IN A SYSTEM CRASH.
*/

#ifndef LIBSLNK_H
#define LIBSLNK_H

#include <stdint.h>


// ShellLinkHeader Section
#include "LinkFlags.h"
#include "FileAttributes.h"
#include "HotKey.h"

// LinkTargetIDList Section
#include "IDList.h"

// StringData Section
#include "StringData.h"


struct MSShellLink_ShellLinkHeader {
	uint32_t HeaderSize;
	uint32_t LinkCLSID1;			// 128-bit integer
	uint32_t LinkCLSID2;			// 128-bit integer
	uint64_t LinkCLSID3;			// 128-bit integer
	uint32_t LinkFlags;
	uint32_t FileAttributes;
	uint64_t CreationTime;
	uint64_t AccessTime;
	uint64_t WriteTime;
	uint32_t FileSize;
	uint32_t IconIndex;
	uint32_t ShowCommand;
	uint16_t HotKey;
	uint16_t Reserved1;
	uint32_t Reserved2;
	uint32_t Reserved3;
};

struct MSShellLink_LinkTargetIDList {
	uint16_t IDListSize;
	uint8_t *IDList;
	uint16_t TerminalID;
};

struct MSShellLink_LinkInfo {
	uint32_t LinkInfoSize;
	// TODO: Implement LinkInfo section
};


// String data
struct StringData {
	uint16_t CountCharacters;
	wchar_t *String;
};

struct MSShellLink_StringData {
	struct StringData NameString;
	struct StringData RelativePath;
	struct StringData WorkingDir;
	struct StringData CommandLineArguments;
	struct StringData IconLocation;
};

struct MSShellLink_ExtraData {
	// TODO: Implement ExtraData section
	uint32_t TerminalBlock;
};



// General ShellLink Container
struct MSShellLink {
	struct MSShellLink_ShellLinkHeader ShellLinkHeader;
	struct MSShellLink_LinkTargetIDList LinkTargetIDList;
	struct MSShellLink_LinkInfo LinkInfo;
	struct MSShellLink_StringData StringData;
	struct MSShellLink_ExtraData ExtraData;
};




// Functions definitions
int LnkInit(struct MSShellLink *Link);

int LnkBuild(struct MSShellLink *Link, const wchar_t *Path);

int LnkFree(struct MSShellLink *Link);

#endif /* LIBSLNK_H */
