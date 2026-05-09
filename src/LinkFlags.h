/*
 * @file LinkFlags.h
 * @brief Link Flags definitions for MS-SHLLINK shell link files
 * 
 * @details This header defines the bit flags used in the LinkFlags field of the
 * ShellLinkHeader structure. These flags indicate which optional sections and
 * features are present in a shell link file.
 * 
 * @see [MS-SHLLINK] section 2.1.1
 */

#ifndef LINKFLAGS_H
#define LINKFLAGS_H

#include "LibSLNK.h"

/*
 * @defgroup LinkFlags_Definitions Link Flags Bit Definitions
 * @brief Bit flags indicating presence of optional shell link sections and features
 * 
 * @details The LinkFlags field in ShellLinkHeader is a 32-bit value where each bit
 * indicates the presence or enablement of optional data sections and behavioral flags.
 * Multiple flags can be set simultaneously.
 * 
 * @see [MS-SHLLINK] section 2.1.1
 * @{
 */

/*
 * Bit 0: LinkTargetIDList section is present
 * @details If set, a LinkTargetIDList section follows the ShellLinkHeader
 */
#define LNK_FLAG_HAS_TARGET_IDLIST					0x00000001

/*
 * Bit 1: LinkInfo section is present
 * @details If set, a LinkInfo section is present in the file
 */
#define LNK_FLAG_HAS_LINK_INFO						0x00000002

/*
 * Bit 2: NameString is present in StringData section
 * @details If set, the StringData section contains a NameString (display name)
 */
#define LNK_FLAG_HAS_NAME							0x00000004

/*
 * Bit 3: RelativePath is present in StringData section
 * @details If set, the StringData section contains a RelativePath string
 */
#define LNK_FLAG_HAS_RELATIVE_PATH					0x00000008

/*
 * Bit 4: WorkingDir is present in StringData section
 * @details If set, the StringData section contains a WorkingDir string
 */
#define LNK_FLAG_HAS_WORKING_DIR					0x00000010

/*
 * Bit 5: CommandLineArguments is present in StringData section
 * @details If set, the StringData section contains CommandLineArguments
 */
#define LNK_FLAG_HAS_ARGUMENTS						0x00000020

/*
 * Bit 6: IconLocation is present in StringData section
 * @details If set, the StringData section contains an IconLocation string
 */
#define LNK_FLAG_HAS_ICON_LOCATION					0x00000040

/*
 * Bit 7: Strings are in Unicode format (UTF-16LE)
 * @details If set, all string fields in StringData use Unicode (UTF-16LE) encoding.
 * If clear, strings use ANSI (8-bit) encoding
 */
#define LNK_FLAG_IS_UNICODE							0x00000080

/*
 * Bit 8: Force no LinkInfo section
 * @details If set, the LinkInfo section MUST be ignored if present.
 * The LinkTargetIDList MUST be used to locate the target
 */
#define LNK_FLAG_FORCE_NO_LINK_INFO					0x00000100

/*
 * Bit 9: Expandable environment variable string present
 * @details If set, an EnvironmentVariableDataBlock is present in ExtraData
 */
#define LNK_FLAG_HAS_EXP_STRING						0x00000200

/*
 * Bit 10: Run link target in separate process
 * @details If set, the target should be run in a separate process
 * (prevents inheritance of process environment)
 */
#define LNK_FLAG_RUN_IN_SEPARATE_PROCESS			0x00000400

 /*
  * Bit 11: Unused 1
  * @details This bit is undefined and ignored. The flag is
  * provided anyways to ensure compatibility with eventual
  * future updates.
  */
#define LNK_FLAG_UNUSED_1							0x00000800

/*
 * Bit 12: Darwin (macOS) system data present
 * @details If set, a DarwinDataBlock is present in ExtraData
 */
#define LNK_FLAG_HAS_DARWIN_ID						0x00001000

/*
 * Bit 13: Run as user (prompt for credentials if needed)
 * @details If set, the link should prompt for user credentials if necessary
 */
#define LNK_FLAG_RUN_AS_USER						0x00002000

/*
 * Bit 14: Expandable environment variable icon present
 * @details If set, an IconEnvironmentDataBlock is present in ExtraData
 */
#define LNK_FLAG_HAS_EXP_ICON						0x00004000

/*
 * Bit 15: Disable PIDLAlias (do not use ItemIDList alias)
 * @details If set, the LinkTargetIDList should not be treated as an alias
 */
#define LNK_FLAG_NO_PIDL_ALIAS						0x00008000
 
 /*
   * Bit 16: Unused 2
   * @details This bit is undefined and ignored. The flag is
   * provided anyways to ensure compatibility with eventual
   * future updates.
   */
#define LNK_FLAG_UNUSED_2							0x00010000

/*
 * Bit 17: Run with compatibility layer shim
 * @details If set, a ShimDataBlock is present in ExtraData containing
 * compatibility layer information
 */
#define LNK_FLAG_RUN_WITH_SHIM_LAYER				0x00020000

/*
 * Bit 18: Force no link tracking
 * @details If set, distributed link tracking (via TrackerDataBlock) MUST be ignored
 */
#define LNK_FLAG_FORCE_NO_LINK_TRACK				0x00040000

/*
 * Bit 19: Enable target metadata
 * @details If set, a PropertyStoreDataBlock is present in ExtraData
 * containing serialized property store data
 */
#define LNK_FLAG_ENABLE_TARGET_METADATA				0x00080000

/*
 * Bit 20: Disable link path tracking
 * @details If set, link path tracking should not be used to update the link
 */
#define LNK_FLAG_DISABLE_LINK_PATH_TRACKING			0x00100000

/*
 * Bit 21: Disable known folder tracking
 * @details If set, known folder tracking should not be used
 */
#define LNK_FLAG_DISABLE_KNOWN_FOLDER_TRACKING		0x00200000

/*
 * Bit 22: Disable known folder alias
 * @details If set, do not resolve the known folder alias
 */
#define LNK_FLAG_DISABLE_KNOWN_FOLDER_ALIAS			0x00400000

/*
 * Bit 23: Allow link to link
 * @details If set, the link target can itself be a shell link
 */
#define LNK_FLAG_ALLOW_LINK_TO_LINK					0x00800000

/*
 * Bit 24: Unalias on save
 * @details If set, the link should be unaliased when saved
 */
#define LNK_FLAG_UNALIAS_ON_SAVE					0x01000000

/*
 * Bit 25: Prefer environment path resolution
 * @details If set, use environment variable paths for resolution
 * before other methods
 */
#define LNK_FLAG_PREFER_ENVIRONMENT_PATH			0x02000000

/*
 * Bit 26: Keep local IDList for UNC targets
 * @details If set, maintain the local IDList even for UNC (network) paths
 */
#define LNK_FLAG_KEEP_LOCAL_IDLIST_FOR_UNC_TARGET	0x04000000

/* @} */


/*
 * @defgroup LinkFlags_Functions Link Flags Manipulation Functions
 * @brief Functions to check, set, and clear link flags
 * @{
 */

 /*
  * @brief Check if one or more flags are set
  *
  * @details Tests whether the specified flag(s) are set in the LinkFlags field.
  * When checking multiple flags with a combined value (e.g., Flag1 | Flag2),
  * this function returns non-zero if ANY of the specified flags are set.
  *
  * @param[in] Link Pointer to MSShellLink structure
  * @param[in] Flag Flag constant or combination of flags to check
  *
  * @return Non-zero (true) if any of the specified flags are set, 0 (false) if none are set,
  *         negative value on error (e.g., NULL pointer)
  *
  * @see LnkSetFlag(), LnkClearFlag()
  */
int LnkCheckFlag(struct MSShellLink *Link, uint32_t Flag);

/*
 * @brief Set a flag in the LinkFlags field
 * 
 * @details Sets one or more bits in the LinkFlags field of the ShellLinkHeader.
 * Multiple flags can be set by ORing the flag constants together.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * @param[in] Flag Flag constant or combination of flags to set (e.g., LNK_FLAG_HAS_NAME | LNK_FLAG_HAS_ICON_LOCATION)
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see LnkClearFlag(), LnkCheckFlag()
 */
int LnkSetFlag(struct MSShellLink *Link, uint32_t Flag);

/*
 * @brief Clear a flag in the LinkFlags field
 * 
 * @details Clears (resets to 0) one or more bits in the LinkFlags field
 * of the ShellLinkHeader. Multiple flags can be cleared by ORing the flag
 * constants together.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * @param[in] Flag Flag constant or combination of flags to clear
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see LnkSetFlag(), LnkCheckFlag()
 */
int LnkClearFlag(struct MSShellLink *Link, uint32_t Flag);

/* @} */

#endif /* LINKFLAGS_H */
