#ifndef STRINGDATA_H
#define STRINGDATA_H

#include "LibSLNK.h"

#define LNK_SD_NAME_STRING					0x01
#define LNK_SD_RELATIVE_PATH				0x02
#define LNK_SD_WORKING_DIR					0x03
#define LNK_SD_COMMAND_LINE_ARGUMENTS		0x04
#define LNK_SD_ICON_LOCATION				0x05



int LnkSetString(struct MSShellLink *lnk, const wchar_t *data, uint8_t type);
int LnkClearString(struct MSShellLink *lnk, uint8_t type);


#endif /* STRINGDATA_H */
