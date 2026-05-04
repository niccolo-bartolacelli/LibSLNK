#include <Windows.h>
#include <ShlObj_core.h>
#include <stdlib.h>
#include <stdint.h>
#include "LibSLNK.h"
#include "LinkFlags.h"

int LnkSetPath(struct MSShellLink *Link, const wchar_t *path) {
    int offset;
    uint8_t *pidlBuffer;
    LPITEMIDLIST pidl, workPidl;

    pidl = ILCreateFromPathW(path);
    if (!pidl) {
        return 0;
    }


    /* Compute PIDL IDListSize */
    Link->LinkTargetIDList.IDListSize = 0;

    workPidl = pidl;
    while (workPidl->mkid.cb != 0x0000) {
        Link->LinkTargetIDList.IDListSize += workPidl->mkid.cb * sizeof(uint8_t);
        workPidl = (LPITEMIDLIST)((uint8_t *)workPidl + workPidl->mkid.cb);
    }

    Link->LinkTargetIDList.IDListSize += 2 * sizeof(uint8_t);    /* Extra size for TerminalID */


    /* Allocate IDList */
    pidlBuffer = malloc(Link->LinkTargetIDList.IDListSize * sizeof(uint8_t));
    if (!pidlBuffer) {
        return 0;
    }

    /* Populate PIDL Buffer IDList */
    workPidl = pidl;
    offset = 0;
    while (workPidl->mkid.cb != 0x0000) {
        pidlBuffer[offset++] = workPidl->mkid.cb & 0xFF;
        pidlBuffer[offset++] = workPidl->mkid.cb >> 0x8;

        for (int i = 0; i < workPidl->mkid.cb - sizeof(workPidl->mkid.cb); i += 1) {
            pidlBuffer[offset++] = workPidl->mkid.abID[i];
        }

        workPidl = (LPITEMIDLIST)((uint8_t *)workPidl + workPidl->mkid.cb);
    }

    pidlBuffer[offset++] = 0x00;    /* TerminalID */
    pidlBuffer[offset++] = 0x00;

    Link->LinkTargetIDList.IDList = pidlBuffer;  /* Return value */

    ILFree(pidl);

    /* Set HAS_TARGET_IDLIST flag */
    LnkSetFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST);

    return 1;
}
