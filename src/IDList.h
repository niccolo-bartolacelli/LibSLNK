#ifndef IDLIST_H
#define IDLIST_H

#include "LibSLNK.h"

const char *LnkGetPath(struct MSShellLink *Link);
int LnkSetPath(struct MSShellLink *Link, const wchar_t *path);

#endif /* IDLIST_H */
