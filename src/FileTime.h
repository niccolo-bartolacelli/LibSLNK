/**
 * @file FileTime.h
 * @brief Functions to get/set file timestamps stored in a Shell Link (shortcut).
 *
 * These helpers read and write the creation, last access and last write times
 * associated with a `MSShellLink` instance. Timestamps are handled according to
 * the MS-SHLLINK specification for Shell Link binary files.
 *
 * @see MS-SHLLINK: https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */

#ifndef FILETIME_H_
#define FILETIME_H_

#include "LibSLNK.h"

/**
 * @brief Set the creation time for the provided Shell Link.
 *
 * Writes the time value pointed to by `Time` into the link's internal
 * timestamp field that represents the creation time of the target.
 *
 * @param Link Pointer to the `MSShellLink` instance to modify.
 * @param Time Pointer to a `SYSTEMTIME` containing the creation time to set.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkSetCreationTime(struct MSShellLink *Link, const SYSTEMTIME *Time);

/**
 * @brief Set the last access time for the provided Shell Link.
 *
 * Writes the time value pointed to by `Time` into the link's internal
 * timestamp field that represents the last access time of the target.
 *
 * @param Link Pointer to the `MSShellLink` instance to modify.
 * @param Time Pointer to a `SYSTEMTIME` containing the access time to set.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkSetAccessTime(struct MSShellLink *Link, const SYSTEMTIME *Time);

/**
 * @brief Set the last write (modification) time for the provided Shell Link.
 *
 * Writes the time value pointed to by `Time` into the link's internal
 * timestamp field that represents the last write time of the target.
 *
 * @param Link Pointer to the `MSShellLink` instance to modify.
 * @param Time Pointer to a `SYSTEMTIME` containing the write time to set.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkSetWriteTime(struct MSShellLink *Link, const SYSTEMTIME *Time);

/**
 * @brief Get the creation time from the provided Shell Link.
 *
 * Reads the creation timestamp stored in the link and converts/stores it into
 * the `SYSTEMTIME` structure pointed to by `Time`.
 *
 * @param Link Pointer to the `MSShellLink` instance to read from.
 * @param Time Pointer to a `SYSTEMTIME` structure that will receive the value.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkGetCreationTime(struct MSShellLink *Link, SYSTEMTIME *Time);

/**
 * @brief Get the last access time from the provided Shell Link.
 *
 * Reads the last access timestamp stored in the link and converts/stores it
 * into the `SYSTEMTIME` structure pointed to by `Time`.
 *
 * @param Link Pointer to the `MSShellLink` instance to read from.
 * @param Time Pointer to a `SYSTEMTIME` structure that will receive the value.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkGetAccessTime(struct MSShellLink *Link, SYSTEMTIME *Time);

/**
 * @brief Get the last write (modification) time from the provided Shell Link.
 *
 * Reads the last write timestamp stored in the link and converts/stores it
 * into the `SYSTEMTIME` structure pointed to by `Time`.
 *
 * @param Link Pointer to the `MSShellLink` instance to read from.
 * @param Time Pointer to a `SYSTEMTIME` structure that will receive the value.
 * @return int Returns non-zero on success, 0 on error.
 *
 * @see MS-SHLLINK specification (timestamp fields)
 *      https://learn.microsoft.com/openspecs/windows_protocols/ms-shllink/
 */
int LnkGetWriteTime(struct MSShellLink *Link, SYSTEMTIME *Time);

#endif /* FILETIME_H_ */
