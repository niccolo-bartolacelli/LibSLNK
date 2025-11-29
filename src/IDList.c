#include <Windows.h>
#include <ShlObj_core.h>
#include <stdlib.h>
#include <stdint.h>
#include "LibSLNK.h"
#include "LinkFlags.h"

int LnkSetPath(struct MSShellLink *lnk, const wchar_t *path) {
    LPITEMIDLIST pidl, workPidl;

    pidl = ILCreateFromPathW(path);
    if (!pidl) return 0;


    // Compute PIDL IDListSize
    lnk->LinkTargetIDList.IDListSize = 0;

    workPidl = pidl;
    while (workPidl->mkid.cb != 0x0000) {
        lnk->LinkTargetIDList.IDListSize += workPidl->mkid.cb * sizeof(uint8_t);
        workPidl = (LPITEMIDLIST)((uint8_t *)workPidl + workPidl->mkid.cb);
    }

    lnk->LinkTargetIDList.IDListSize += 2 * sizeof(uint8_t);    // Extra size for TerminalID


    // Allocate sufficient space for IDList
    uint8_t *pidlBuffer = malloc(lnk->LinkTargetIDList.IDListSize * sizeof(uint8_t));
    if (!pidlBuffer) return 0;

    // Populate PIDL Buffer IDList
    workPidl = pidl;
    int offset = 0;
    while (workPidl->mkid.cb != 0x0000) {
        pidlBuffer[offset++] = workPidl->mkid.cb & 0xFF;
        pidlBuffer[offset++] = workPidl->mkid.cb >> 0x8;

        for (int i = 0; i < workPidl->mkid.cb - sizeof(workPidl->mkid.cb); i += 1) {
            pidlBuffer[offset++] = workPidl->mkid.abID[i];
        }

        workPidl = (LPITEMIDLIST)((uint8_t *)workPidl + workPidl->mkid.cb);
    }

    pidlBuffer[offset++] = 0x00;    // TerminalID
    pidlBuffer[offset++] = 0x00;

    lnk->LinkTargetIDList.IDList = pidlBuffer;  // Return value
    lnk->LinkTargetIDList.TerminalID = 0x0000;

    ILFree(pidl);

    // Set HAS_TARGET_IDLIST flag
    LnkSetFlag(lnk, LNK_FLAG_HAS_TARGET_IDLIST);

    return 1;
}
