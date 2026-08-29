#ifndef LNKBUILDER_H
#define LNKBUILDER_H

#include <stdio.h>
#include "LibSLNK.h"

int BuildShellLinkHeaderToFile(struct MSShellLink *Link, FILE *fptr);
int BuildLinkTargetIDListToFile(struct MSShellLink *Link, FILE *fptr);
// TODO: int BuildLinkInfoToFile(struct MSShellLink *lnk, FILE *fptr);
int BuildStringDataToFile(struct MSShellLink *Link, FILE *fptr);
int BuildExtraDataToFile(struct MSShellLink *lnk, FILE *fptr);

#endif /* LNKBUILDER_H */
