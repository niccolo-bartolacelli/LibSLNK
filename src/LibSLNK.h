#ifndef LIBSLNK_H
#define LIBSLNK_H

#include <stdint.h>
#include <stdio.h>

/**
 * @file LibSLNK.h
 * @brief MS-SHLLINK Shell Link (.LNK) file format parser
 * @details This library implements parsing and building of Windows Shell Link (.LNK) files
 * according to the Microsoft MS-SHLLINK specification. It provides data structures and
 * functions to read, interpret, and manipulate shell link file contents.
 * 
 * @see [MS-SHLLINK]: Shell Link (.LNK) Binary File Format Specification
 * @author Niccolò Bartolacelli
 */

/* ShellLinkHeader Section */
#include "LinkFlags.h"
#include "FileAttributes.h"
#include "HotKey.h"

/* LinkTargetIDList Section */
#include "IDList.h"

/* StringData Section */
#include "StringData.h"


/**
 * @struct ShellLinkHeader
 * @brief ShellLinkHeader section of a shell link file
 * 
 * @details The ShellLinkHeader is a fixed-size structure that contains metadata about
 * the shell link. It appears at the beginning of every shell link file and contains
 * information about file size, access times, and display properties.
 * 
 * @see [MS-SHLLINK] section 2.1
 */
struct ShellLinkHeader {
	uint32_t HeaderSize;                ///< Must be 0x0000004C (76 bytes)
	uint32_t LinkCLSID_1;               ///< GUID (part 1/3): bytes 0-3. Must be {00021401-0000-0000-C000-000000000046}
	uint32_t LinkCLSID_2;               ///< GUID (part 2/3): bytes 4-7
	uint64_t LinkCLSID_3;               ///< GUID (part 3/3): bytes 8-15
	uint32_t LinkFlags;                 ///< Flags specifying which fields are present (bit flags)
	uint32_t FileAttributes;            ///< FAT file attributes of the link target
	uint64_t CreationTime;              ///< Windows FILETIME structure for creation time
	uint64_t AccessTime;                ///< Windows FILETIME structure for last access time
	uint64_t WriteTime;                 ///< Windows FILETIME structure for last write time
	uint32_t FileSize;                  ///< Size of the link target in bytes
	uint32_t IconIndex;                 ///< Index of icon to use from associated file
	uint32_t ShowCommand;               ///< How the target window should be displayed (SW_NORMAL, SW_MAXIMIZED, SW_MINIMIZED)
	uint16_t HotKey;                    ///< Hotkey for launching the link target
	uint16_t Reserved1;                 ///< Reserved field, must be zero
	uint32_t Reserved2;                 ///< Reserved field, must be zero
	uint32_t Reserved3;                 ///< Reserved field, must be zero
};


/**
 * @struct ItemID
 * @brief Single item identifier within a LinkTargetIDList
 * 
 * @details Each ItemID represents a level in the path hierarchy, typically
 * corresponding to a folder or file in the directory structure.
 * 
 * @see [MS-SHLLINK] section 2.2
 */
struct ItemID {
	uint16_t ItemIDSize;                ///< Size of this ItemID structure
	uint8_t *Data;                      ///< Item identifier data (format depends on item type)
};

/**
 * @struct LinkTargetIDList
 * @brief Path to the link target expressed as a series of ItemID structures
 * 
 * @details The LinkTargetIDList section contains a sequence of ItemID structures
 * that form a path to the link target. This is used for resolving the target
 * when the primary path information is unavailable.
 * 
 * @see [MS-SHLLINK] section 2.2
 */
struct LinkTargetIDList {
	uint16_t IDListSize;                ///< Total size of IDList data including this field
	struct ItemID *IDList;              ///< Array of ItemID structures forming the path
};

/**
 * @struct LinkInfoHeader
 * @brief Header information for the LinkInfo section
 * 
 * @details Contains offsets and flags describing the LinkInfo structure layout
 * and which fields are present.
 * 
 * @see [MS-SHLLINK] section 2.3
 */
struct LinkInfoHeader {
	uint32_t LinkInfoSize;              ///< Total size of LinkInfo structure in bytes
	uint32_t LinkInfoHeaderSize;        ///< Size of LinkInfoHeader (7C or 84 bytes)
	uint32_t LinkInfoFlags;             ///< Flags indicating which optional fields are present
	uint32_t VolumeIDOffset;            ///< Offset to VolumeID structure (relative to LinkInfo start)
	uint32_t LocalBasePathOffset;       ///< Offset to LocalBasePath string (ANSI)
	uint32_t CommonNetworkRelativeLinkOffset;  ///< Offset to CommonNetworkRelativeLink structure
	uint32_t CommonPathSuffixOffset;    ///< Offset to CommonPathSuffix string
	uint32_t LocalBasePathOffsetUnicode;       ///< Offset to LocalBasePath string (Unicode, optional)
	uint32_t CommonPathSuffixOffsetUnicode;    ///< Offset to CommonPathSuffix string (Unicode, optional)
};

/**
 * @struct VolumeID
 * @brief Volume information for local paths
 * 
 * @details Describes the drive and volume where the link target is located,
 * including drive type, serial number, and volume label.
 * 
 * @see [MS-SHLLINK] section 2.3.1
 */
struct VolumeID {
	uint32_t VolumeIDSize;              ///< Size of this VolumeID structure
	uint32_t DriveType;                 ///< Type of drive (DRIVE_UNKNOWN, DRIVE_REMOVABLE, DRIVE_FIXED, DRIVE_REMOTE, DRIVE_CDROM, DRIVE_RAMDISK)
	uint32_t DriveSerialNumber;         ///< Serial number of the volume
	uint32_t VolumeLabelOffset;         ///< Offset to volume label (ANSI), relative to VolumeID start
	uint32_t VolumeLabelOffsetUnicode;  ///< Offset to volume label (Unicode), relative to VolumeID start
	uint8_t *Data;                      ///< Parsed volume data containing label and other information
};

/**
 * @struct CommonNetworkRelativeLink
 * @brief Network resource information for network paths
 * 
 * @details Contains details about network shares and devices for link targets
 * on network paths.
 * 
 * @see [MS-SHLLINK] section 2.3.2
 */
struct CommonNetworkRelativeLink {
	uint32_t CommonNetworkRelativeLinkSize;    ///< Size of this structure
	uint32_t CommonNetworkRelativeLinkFlags;   ///< Flags indicating which fields are valid
	uint32_t NetNameOffset;                    ///< Offset to network name string (ANSI)
	uint32_t DeviceNameOffset;                 ///< Offset to device name string (ANSI)
	uint32_t NetworkProviderType;              ///< Type of network provider
	uint32_t NetNameOffsetUnicode;             ///< Offset to network name string (Unicode)
	uint32_t DeviceNameOffsetUnicode;          ///< Offset to device name string (Unicode)
	char *NetName;                             ///< Network name (ANSI) - e.g., "\\server\share"
	char *DeviceName;                          ///< Device name (ANSI) - e.g., "Z:"
	wchar_t *NetNameUnicode;                   ///< Network name (Unicode)
	wchar_t *DeviceNameUnicode;                ///< Device name (Unicode)
};

/**
 * @struct LinkInfo
 * @brief LinkInfo section containing path information for the link target
 * 
 * @details The LinkInfo section specifies how to locate the link target,
 * including volume information for local paths and network resource
 * information for remote paths.
 * 
 * @see [MS-SHLLINK] section 2.3
 */
struct LinkInfo {
	struct LinkInfoHeader LinkInfoHeader;      ///< Header with offsets and flags
	struct VolumeID VolumeID;                  ///< Volume information (for local paths)
	char *LocalBasePath;                       ///< Base path on local volume (ANSI)
	struct CommonNetworkRelativeLink CommonNetworkRelativeLink;  ///< Network information (for network paths)
	char *CommonPathSuffix;                    ///< Path suffix common to both local and network (ANSI)
	wchar_t *LocalBasePathUnicode;             ///< Base path on local volume (Unicode)
	wchar_t *CommonPathSuffixUnicode;          ///< Path suffix (Unicode)
};


/**
 * @struct String
 * @brief A string with both ANSI and Unicode variants
 * 
 * @details Used throughout the shell link format to store text in both
 * ANSI (CP850/CP437) and Unicode (UTF-16LE) encodings.
 */
struct String {
	uint16_t CountCharacters;           ///< Number of characters (excluding null terminator)
	char *String;                       ///< ANSI encoded string
	wchar_t *StringUnicode;             ///< Unicode encoded string
};

/**
 * @struct StringData
 * @brief StringData section with descriptive strings about the link
 * 
 * @details The StringData section contains optional human-readable strings
 * that describe the link target and its usage.
 * 
 * @see [MS-SHLLINK] section 2.4
 */
struct StringData {
	struct String NameString;           ///< Display name of the link target
	struct String RelativePath;         ///< Relative path to the link target
	struct String WorkingDir;           ///< Working directory to use when executing target
	struct String CommandLineArguments; ///< Command-line arguments to pass to target
	struct String IconLocation;         ///< Location of icon file for the link
};


/**
 * @struct ConsoleDataBlock
 * @brief Console settings for console application shortcuts
 * 
 * @details Stores window and console properties for shortcuts that launch
 * console/command-line applications.
 * 
 * @see [MS-SHLLINK] section 2.5.1
 */
struct ConsoleDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000002)
	uint16_t FillAttributes;            ///< Console fill attributes for normal text
	uint16_t PopupFillAttributes;       ///< Console fill attributes for popup text
	uint16_t ScreenBufferSizeX;         ///< Screen buffer width in columns
	uint16_t ScreenBufferSizeY;         ///< Screen buffer height in rows
	uint16_t WindowSizeX;               ///< Window width in columns
	uint16_t WindowSizeY;               ///< Window height in rows
	uint16_t WindowOriginX;             ///< Window X coordinate
	uint16_t WindowOriginY;             ///< Window Y coordinate
	uint32_t Unused1;                   ///< Unused field
	uint32_t Unused2;                   ///< Unused field
	uint16_t FontSize;                  ///< Font size in points
	uint16_t FontFamily;                ///< Font family
	uint16_t FontWeight;                ///< Font weight
	wchar_t FontName[32];               ///< Font name (Unicode)
	uint16_t CursorSize;                ///< Cursor size percentage
	uint8_t FullScreen;                 ///< Full screen mode flag
	uint8_t QuickEdit;                  ///< Quick edit mode flag
	uint8_t InsertMode;                 ///< Insert mode flag
	uint8_t AutoPosition;               ///< Auto-position window flag
	uint16_t HistoryBufferSize;         ///< Command history buffer size
	uint16_t NumberOfHistoryBuffers;    ///< Number of history buffers
	uint8_t HistoryNoDup;               ///< No duplicate history entries flag
};

/**
 * @struct ConsoleFEDataBlock
 * @brief Console code page information for Far East applications
 * 
 * @see [MS-SHLLINK] section 2.5.2
 */
struct ConsoleFEDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000004)
	uint16_t CodePage;                  ///< Code page for Far East language support
};

/**
 * @struct DarwinDataBlock
 * @brief Darwin (macOS) compatibility data
 * 
 * @see [MS-SHLLINK] section 2.5.3
 */
struct DarwinDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000001)
	char *DarwinDataAnsi;               ///< Darwin/Mac path (ANSI)
	wchar_t *DarwinDataUnicode;         ///< Darwin/Mac path (Unicode)
};

/**
 * @struct EnvironmentVariableDataBlock
 * @brief Environment variable expansion for target paths
 * 
 * @details Allows the target path to reference environment variables like %USERPROFILE%
 * for dynamic path resolution.
 * 
 * @see [MS-SHLLINK] section 2.5.4
 */
struct EnvironmentVariableDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000001)
	char *TargetAnsi;                   ///< Target path with environment variables (ANSI)
	wchar_t *TargetUnicode;             ///< Target path with environment variables (Unicode)
};

/**
 * @struct IconEnvironmentDataBlock
 * @brief Environment variable expansion for icon paths
 * 
 * @see [MS-SHLLINK] section 2.5.5
 */
struct IconEnvironmentDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000007)
	char *IconEnvironmentDataAnsi;      ///< Icon path with environment variables (ANSI)
	wchar_t *IconEnvironmentDataUnicode;///< Icon path with environment variables (Unicode)
};


/**
 * @struct KnownFolderDataBlock
 * @brief Well-known folder reference
 * 
 * @details References a known folder by GUID instead of path, allowing
 * the link to resolve even if the physical path changes.
 * 
 * @see [MS-SHLLINK] section 2.5.6
 */
struct KnownFolderDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA000000B)
	uint8_t KnownFolderID[16];          ///< GUID of the known folder
	uint32_t Offset;                    ///< Offset within the known folder
};

/**
 * @struct PropertyStoreDataBlock
 * @brief Property store containing additional metadata
 * 
 * @details Stores serialized property store data with extended attributes
 * about the link target.
 * 
 * @see [MS-SHLLINK] section 2.5.7
 */
struct PropertyStoreDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000009)
	uint8_t *PropertyStore;             ///< Serialized property store data
	uint32_t PropertyStoreSize;         ///< Size of property store data
};

/**
 * @struct ShimDataBlock
 * @brief Application shim (compatibility layer) information
 * 
 * @details References compatibility shims used to run the target application
 * in compatibility mode.
 * 
 * @see [MS-SHLLINK] section 2.5.8
 */
struct ShimDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000008)
	wchar_t *LayerName;                 ///< Compatibility layer name (Unicode)
};

/**
 * @struct SpecialFolderDataBlock
 * @brief Special folder reference using integer identifiers
 * 
 * @details References special folders like Desktop, StartMenu, etc. using
 * numeric identifiers.
 * 
 * @see [MS-SHLLINK] section 2.5.9
 */
struct SpecialFolderDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000005)
	uint32_t SpecialFolderID;           ///< Special folder identifier (CSIDL_* constants)
};

/**
 * @struct TrackerDataBlock
 * @brief Object identifier tracking data
 * 
 * @details Contains machine ID and distributed link tracking information
 * to locate moved files on the network.
 * 
 * @see [MS-SHLLINK] section 2.5.10
 */
struct TrackerDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA0000003)
	uint32_t Length;                    ///< Length of MachineID and Droid data
	uint32_t Version;                   ///< Version of the tracker block
	char MachineID[16];                 ///< Machine identifier
	uint8_t *Droid;                     ///< Distributed link tracking object identifier (GUID)
	uint8_t *DroidBirth;                ///< Birth GUID for the object
};

/**
 * @struct VistaAndAboveIDListDataBlock
 * @brief Enhanced IDList for Windows Vista and later systems
 * 
 * @details Provides an additional IDList structure for better compatibility
 * with Windows Vista and later versions.
 * 
 * @see [MS-SHLLINK] section 2.5.11
 */
struct VistaAndAboveIDListDataBlock {
	uint32_t BlockSize;                 ///< Size of this data block
	uint32_t BlockSignature;            ///< Block signature (0xA000000C)
	uint8_t *IDList;                    ///< Enhanced IDList data
	uint32_t IDListSize;                ///< Size of IDList data
};


/**
 * @struct ExtraData
 * @brief ExtraData section containing optional data blocks
 * 
 * @details The ExtraData section is a sequence of data blocks that contain
 * optional metadata about the link. Each block is optional and may be NULL.
 * The terminal block has a signature of 0x00000000.
 * 
 * @see [MS-SHLLINK] section 2.5
 */
struct ExtraData {
	struct ConsoleDataBlock *ConsoleDataBlock;                      ///< Optional console properties
	struct ConsoleFEDataBlock *ConsoleFEDataBlock;                  ///< Optional Far East console settings
	struct DarwinDataBlock *DarwinDataBlock;                        ///< Optional Darwin/macOS info
	struct EnvironmentVariableDataBlock *EnvironmentVariableDataBlock;  ///< Optional environment variable expansion
	struct IconEnvironmentDataBlock *IconEnvironmentDataBlock;      ///< Optional icon path environment variable
	struct KnownFolderDataBlock *KnownFolderDataBlock;              ///< Optional known folder reference
	struct PropertyStoreDataBlock *PropertyStoreDataBlock;          ///< Optional property store
	struct ShimDataBlock *ShimDataBlock;                            ///< Optional compatibility shim
	struct SpecialFolderDataBlock *SpecialFolderDataBlock;          ///< Optional special folder reference
	struct TrackerDataBlock *TrackerDataBlock;                      ///< Optional object tracking info
	struct VistaAndAboveIDListDataBlock *VistaAndAboveIDListDataBlock;  ///< Optional enhanced IDList
	uint32_t TerminalBlock;                                         ///< Terminal block signature (0x00000000)
};



/**
 * @struct MSShellLink
 * @brief Complete MS Shell Link file structure
 * 
 * @details This is the main structure that represents the entire contents
 * of a .LNK (shell link) file. It contains all the major sections in order:
 * ShellLinkHeader, LinkTargetIDList, LinkInfo, StringData, and ExtraData.
 * 
 * @see [MS-SHLLINK]: Shell Link (.LNK) Binary File Format Specification
 */
struct MSShellLink {
	struct ShellLinkHeader ShellLinkHeader;      ///< Fixed-size header (always present, 76 bytes)
	struct LinkTargetIDList LinkTargetIDList;    ///< Optional IDList path information
	struct LinkInfo LinkInfo;                    ///< Optional path information (local or network)
	struct StringData StringData;                ///< Optional descriptive strings
	struct ExtraData ExtraData;                  ///< Optional additional data blocks
};




/**
 * @defgroup LibSLNK_Functions LibSLNK API Functions
 * @{
 */

/**
 * @brief Initialize a new MSShellLink structure
 * 
 * @details Allocates and initializes a new MSShellLink structure with all
 * fields set to zero/NULL.
 * 
 * @return Pointer to newly allocated MSShellLink structure, or NULL if allocation fails
 * 
 * @see LnkFree()
 */
struct MSShellLink *LnkInit(void);

/**
 * @brief Parse and build a MSShellLink from a .LNK file
 * 
 * @details Reads and parses a shell link file from the provided FILE stream
 * into the MSShellLink structure. The file should be opened in binary read mode.
 * 
 * @param[out] Link Pointer to MSShellLink structure to populate
 * @param[in] File Pointer to opened FILE stream (opened with "rb" mode)
 * 
 * @return 0 on success, negative value on parsing error
 * 
 * @see LnkInit(), LnkFree()
 */
int LnkBuild(struct MSShellLink *Link, const FILE *File);

/**
 * @brief Free all allocated memory in a MSShellLink structure
 * 
 * @details Releases all dynamically allocated memory within the MSShellLink
 * structure and all nested structures. Sets all pointers to NULL.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure to free
 * 
 * @return 0 on success, negative value on error
 * 
 * @see LnkInit()
 */
int LnkFree(struct MSShellLink *Link);

/** @} */

#endif /* LIBSLNK_H */
