#ifndef LNKBUILDER_H
#define LNKBUILDER_H

#include <stdio.h>
#include "LibSLNK.h"

int BuildShellLinkHeaderToFile(struct MSShellLink *lnk, FILE *fptr);
int BuildLinkTargetIDListToFile(struct MSShellLink *lnk, FILE *fptr);
// TODO: int BuildLinkInfoToFile(struct MSShellLink *lnk, FILE *fptr);
int BuildStringDataToFile(struct MSShellLink *lnk, FILE *fptr);
// TODO: int BuildExtraDataToFile(struct MSShellLink *lnk, FILE *fptr);

#endif /* LNKBUILDER_H */
