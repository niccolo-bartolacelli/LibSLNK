/*
 * @file FileAttributes.h
 * @brief File Attributes definitions for MS-SHLLINK shell link files
 * 
 * @details This header defines the bit flags used in the FileAttributes field
 * of the ShellLinkHeader structure. These flags indicate the FAT file attributes
 * of the link target file or folder.
 * 
 * @see [MS-SHLLINK] section 2.1.2
 */

#ifndef FILEATTRIBUTES_H
#define FILEATTRIBUTES_H

#include "LibSLNK.h"

/*
 * @defgroup FileAttributes_Definitions File Attributes Bit Definitions
 * @brief Bit flags indicating FAT file attributes of the link target
 * 
 * @details The FileAttributes field in ShellLinkHeader is a 32-bit value where
 * each bit corresponds to a standard FAT file attribute. These attributes describe
 * properties of the link target file or directory. Multiple attributes can be
 * set simultaneously.
 * 
 * @see [MS-SHLLINK] section 2.1.2
 * @{
 */

/*
 * Bit 0: Read-only file attribute
 * @details If set, the file or directory is read-only: for a file,
 * applications can read the file but cannot write to it or delete it;
 * for a directory, applications cannot delete the directory.
 */
#define LNK_FILE_ATTRIBUTE_READONLY            0x00000001

/*
 * Bit 1: Hidden file attribute
 * @details If set, the file od directory is hidden from normal directory listings
 */
#define LNK_FILE_ATTRIBUTE_HIDDEN				0x00000002

/*
 * Bit 2: System file attribute
 * @details If set, the file is a system file critical to operating system functionality
 */
#define LNK_FILE_ATTRIBUTE_SYSTEM				0x00000004

/*
 * Bit 3: Reserved (unused)
 * @details Reserved for future use. Should be zero in well-formed link files
 */
#define LNK_FILE_ATTRIBUTE_RESERVED_1			0x00000008

/*
 * Bit 4: Directory attribute
 * @details If set, the link target is a directory rather than a file
 */
#define LNK_FILE_ATTRIBUTE_DIRECTORY			0x00000010

/*
 * Bit 5: Archive attribute
 * @details If set, the file has been modified since the last backup
 */
#define LNK_FILE_ATTRIBUTE_ARCHIVE				0x00000020

/*
 * Bit 6: Reserved (unused)
 * @details Reserved for future use. Should be zero in well-formed link files
 */
#define LNK_FILE_ATTRIBUTE_RESERVED_2			0x00000040

/*
 * Bit 7: Normal file attribute
 * @details If set, the file has no special attributes. Usually set alone when
 * no other attributes apply
 */
#define LNK_FILE_ATTRIBUTE_NORMAL				0x00000080

/*
 * Bit 8: Temporary file attribute
 * @details If set, the file is temporary and may be deleted by the system
 */
#define LNK_FILE_ATTRIBUTE_TEMPORARY			0x00000100

/*
 * Bit 9: Sparse file attribute
 * @details If set, the file is a sparse file with sections that may be unallocated
 */
#define LNK_FILE_ATTRIBUTE_SPARSE_FILE			0x00000200

/*
 * Bit 10: Reparse point attribute
 * @details If set, the file is a reparse point (e.g., symbolic link, junction)
 */
#define LNK_FILE_ATTRIBUTE_REPARSE_POINT		0x00000400

/*
 * Bit 11: Compressed file attribute
 * @details If set, the file is compressed using NTFS compression
 */
#define LNK_FILE_ATTRIBUTE_COMPRESSED			0x00000800

/*
 * Bit 12: Offline file attribute
 * @details If set, the file data has been moved to offline storage (e.g., tape)
 */
#define LNK_FILE_ATTRIBUTE_OFFLINE				0x00001000

/*
 * Bit 13: Not content indexed attribute
 * @details If set, the file is not indexed by the system content indexer
 */
#define LNK_FILE_ATTRIBUTE_NOT_CONTENT_INDEXED	0x00002000

/*
 * Bit 14: Encrypted file attribute
 * @details If set, the file is encrypted using EFS (Encrypting File System)
 */
#define LNK_FILE_ATTRIBUTE_ENCRYPTED			0x00004000

/* @} */


/*
 * @defgroup FileAttributes_Functions File Attributes Manipulation Functions
 * @brief Functions to check, set, and clear file attributes
 * @{
 */

/*
 * @brief Check (test) a file attribute
 * 
 * @details Tests whether the specified file attribute(s) are set in the
 * FileAttributes field of the ShellLinkHeader.
 * When checking multiple attributes with a combined value (e.g., FileAttribute1 | FileAttribute2),
 * this function returns non-zero if ANY of the specified attributes are set.
 * 
 * @param[in] Link Pointer to MSShellLink structure
 * @param[in] FileAttribute File attribute constant or combination of attributes to test
 *            (e.g., LNK_FILE_ATTRIBUTE_READONLY | LNK_FILE_ATTRIBUTE_HIDDEN)
 * 
 * @return Non-zero (true) if any of the specified attributes are set,
 *         0 (false) if none are set, negative value on error (e.g., NULL pointer)
 * 
 * @see LnkSetFileAttribute(), LnkClearFileAttribute()
 */
int LnkCheckFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute);

/*
 * @brief Set a file attribute
 * 
 * @details Sets (enables) one or more bits in the FileAttributes field of
 * the ShellLinkHeader. Multiple attributes can be set by ORing the attribute
 * constants together.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * @param[in] FileAttribute File attribute constant or combination of attributes to set
 *            (e.g., LNK_FILE_ATTRIBUTE_ARCHIVE | LNK_FILE_ATTRIBUTE_READONLY)
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see LnkCheckFileAttribute(), LnkClearFileAttribute()
 */
int LnkSetFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute);

/*
 * @brief Clear a file attribute
 * 
 * @details Clears (disables, resets to 0) one or more bits in the FileAttributes
 * field of the ShellLinkHeader. Multiple attributes can be cleared by ORing the
 * attribute constants together.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * @param[in] FileAttribute File attribute constant or combination of attributes to clear
 *            (e.g., LNK_FILE_ATTRIBUTE_READONLY | LNK_FILE_ATTRIBUTE_HIDDEN)
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see LnkCheckFileAttribute(), LnkSetFileAttribute()
 */
int LnkClearFileAttribute(struct MSShellLink *Link, uint32_t FileAttribute);

/* @} */

#endif /* FILEATTRIBUTES_H */
