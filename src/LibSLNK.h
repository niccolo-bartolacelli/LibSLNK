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
