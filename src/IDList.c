#include "IDList.h"

#include <ShlObj_core.h>

#include "LibSLNK.h"


const char *LnkGetPath(struct MSShellLink *Link)
{
    if (!LnkCheckFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST)) {
        return NULL;
    }

    return NULL;
}

int LnkSetPath(struct MSShellLink *Link, const wchar_t *path)
{
    struct ItemID *pidlBuffer;
    size_t pidlBufferLen;
    LPITEMIDLIST pidl, pidl_base_addr;

    pidl = ILCreateFromPathW(path);
    if (!pidl) {
        return 0;
    }
    pidl_base_addr = pidl;

    /* Populate PIDL Buffer IDList */
    pidlBuffer = NULL;
    pidlBufferLen = 0;

    Link->LinkTargetIDList.IDListSize = 0;

    while (pidl->mkid.cb != 0x0000) {
        /* Update effective list size */
        Link->LinkTargetIDList.IDListSize += pidl->mkid.cb;

        /* Add ItemID */
        pidlBuffer = realloc(pidlBuffer, (pidlBufferLen + 1) * sizeof(struct ItemID));

        pidlBuffer[pidlBufferLen].ItemIDSize = pidl->mkid.cb;

        pidlBuffer[pidlBufferLen].Data = malloc(pidl->mkid.cb - sizeof(pidl->mkid.cb));
        for (USHORT i = 0; i < pidl->mkid.cb - sizeof(pidl->mkid.cb); i++) {
            pidlBuffer[pidlBufferLen].Data[i] = pidl->mkid.abID[i];
        }

        pidlBufferLen++;

        pidl = (LPITEMIDLIST)((uint8_t *)pidl + pidl->mkid.cb);
    }

    /* TerminalID is handled as an extra empty ItemID */
    Link->LinkTargetIDList.IDListSize += 2;

    pidlBuffer = realloc(pidlBuffer, (pidlBufferLen + 1) * sizeof(struct ItemID));
    pidlBuffer[pidlBufferLen].ItemIDSize = 0x0000;
    pidlBuffer[pidlBufferLen].Data = NULL;

    Link->LinkTargetIDList.IDList = pidlBuffer;  /* Return value */

    ILFree(pidl_base_addr);

    /* Set HAS_TARGET_IDLIST flag */
    LnkSetFlag(Link, LNK_FLAG_HAS_TARGET_IDLIST);

    return 1;
}
