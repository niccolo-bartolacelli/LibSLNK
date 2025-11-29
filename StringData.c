#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>

#include "StringData.h"
#include "LinkFlags.h"

int LnkSetString(struct MSShellLink *lnk, const wchar_t *data, uint8_t type)
{
	if (lnk == NULL) return 0;

	uint32_t StringDataFlag;
	struct StringData *StringDataRef;


	// Switch type
	switch (type) {
	case LNK_SD_NAME_STRING:
		StringDataFlag = LNK_FLAG_HAS_NAME;
		StringDataRef = &(lnk->StringData.NameString);
		break;
	case LNK_SD_RELATIVE_PATH:
		StringDataFlag = LNK_FLAG_HAS_RELATIVE_PATH;
		StringDataRef = &(lnk->StringData.RelativePath);
		break;
	case LNK_SD_WORKING_DIR:
		StringDataFlag = LNK_FLAG_HAS_WORKING_DIR;
		StringDataRef = &(lnk->StringData.WorkingDir);
		break;
	case LNK_SD_COMMAND_LINE_ARGUMENTS:
		StringDataFlag = LNK_FLAG_HAS_ARGUMENTS;
		StringDataRef = &(lnk->StringData.CommandLineArguments);
		break;
	case LNK_SD_ICON_LOCATION:
		StringDataFlag = LNK_FLAG_HAS_ICON_LOCATION;
		StringDataRef = &(lnk->StringData.IconLocation);
		break;
	default:
		return 0;
	}

	// Main function
	if (!LnkSetFlag(lnk, StringDataFlag)) return 0;

	StringDataRef->CountCharacters = (uint16_t)wcslen(data);

	StringDataRef->String = malloc(StringDataRef->CountCharacters * sizeof(wchar_t));
	if (StringDataRef->String == NULL) return 0;

	wcsncpy(StringDataRef->String, data, StringDataRef->CountCharacters);


	return 1;
}

int LnkClearString(struct MSShellLink *lnk, uint8_t type)
{
	if (lnk == NULL) return 0;

	// TODO: Clear StringData structure

	return 1;
}
