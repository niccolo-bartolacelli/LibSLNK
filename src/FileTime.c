#include "FileTime.h"

#include <timezoneapi.h>

int LnkSetCreationTime(struct MSShellLink *Link, const SYSTEMTIME *Time)
{
	if (!SystemTimeToFileTime(Time, &(Link->ShellLinkHeader.CreationTime))) {
		return 0;
	}

	return 1;
}

int LnkSetAccessTime(struct MSShellLink *Link, const SYSTEMTIME *Time)
{
	if (!SystemTimeToFileTime(Time, &(Link->ShellLinkHeader.AccessTime))) {
		return 0;
	}

	return 1;
}

int LnkSetWriteTime(struct MSShellLink *Link, const SYSTEMTIME *Time)
{
	if (!SystemTimeToFileTime(Time, &(Link->ShellLinkHeader.WriteTime))) {
		return 0;
	}

	return 1;
}


int LnkGetCreationTime(struct MSShellLink *Link, SYSTEMTIME *Time)
{
	if (!FileTimeToSystemTime(&(Link->ShellLinkHeader.CreationTime), Time)) {
		return 0;
	}

	return 1;
}

int LnkGetAccessTime(struct MSShellLink *Link, SYSTEMTIME *Time)
{
	if (!FileTimeToSystemTime(&(Link->ShellLinkHeader.AccessTime), Time)) {
		return 0;
	}

	return 1;
}

int LnkGetWriteTime(struct MSShellLink *Link, SYSTEMTIME *Time)
{
	if (!FileTimeToSystemTime(&(Link->ShellLinkHeader.WriteTime), Time)) {
		return 0;
	}

	return 1;
}
