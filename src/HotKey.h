/*
 * @file HotKey.h
 * @brief HotKey definitions for MS-SHLLINK shell link files
 * 
 * @details This header defines the constants for constructing hotkey values
 * used in the HotKey field of the ShellLinkHeader structure. The hotkey is a
 * 16-bit value combining a virtual key code (low byte) with modifier keys
 * (high byte) that can be used to quickly launch the link target.
 * 
 * The HotKey field format is:
 * - High Byte (bits 15-8): Modifier keys (SHIFT, CTRL, ALT)
 * - Low Byte (bits 7-0): Virtual key code (0-9, A-Z, F1-F24, etc.)
 * 
 * @see [MS-SHLLINK] section 2.1.3
 */

#ifndef HOTKEY_H
#define HOTKEY_H

#include "LibSLNK.h"


/*
 * @defgroup HotKey_Modifiers HotKey Modifier Constants
 * @brief High byte constants for modifier key combinations
 * 
 * @details These constants represent the modifier keys that can be combined
 * in the high byte of the HotKey field. Multiple modifiers can be combined
 * using bitwise OR operations.
 * 
 * Usage example: (VK_M_CONTROL | VK_M_SHIFT) for Ctrl+Shift combination
 * 
 * @see [MS-SHLLINK] section 2.1.3
 * @{
 */

/*
 * No modifier keys
 * @details Used when the hotkey has no modifier keys (high byte = 0x00)
 */
#define VK_M_NONE		0x00

/*
 * SHIFT key modifier
 * @details Bit 0 of the modifier byte. Represents the SHIFT key
 */
#define VK_M_SHIFT		0x01

/*
 * CONTROL (CTRL) key modifier
 * @details Bit 1 of the modifier byte. Represents the CONTROL key
 */
#define VK_M_CONTROL	0x02

/*
 * ALT key modifier
 * @details Bit 2 of the modifier byte. Represents the ALT key
 */
#define VK_M_ALT		0x04

/* @} */


/*
 * @defgroup HotKey_VirtualKeys HotKey Virtual Key Constants
 * @brief Low byte constants for virtual key codes
 * 
 * @details These constants represent virtual key codes that can be used in
 * the low byte of the HotKey field. They correspond to standard Windows
 * virtual key codes.
 * 
 * @see [MS-SHLLINK] section 2.1.3
 * @{
 */

/*
 * @defgroup VK_None No Key
 * @brief No key specified
 * @{
 */

/*
 * No virtual key
 * @details Used when no key is assigned to the hotkey (low byte = 0x00)
 */
#define VK_NONE			0x00

/* @} */


/*
 * @defgroup VK_Numbers Number Keys (0-9)
 * @brief Virtual key codes for numeric keys
 * @{
 */

/*
 * Virtual key code for number 0 key
 */
#define VK_0			0x30

/*
 * Virtual key code for number 1 key
 */
#define VK_1			0x31

/*
 * Virtual key code for number 2 key
 */
#define VK_2			0x32

/*
 * Virtual key code for number 3 key
 */
#define VK_3			0x33

/*
 * Virtual key code for number 4 key
 */
#define VK_4			0x34

/*
 * Virtual key code for number 5 key
 */
#define VK_5			0x35

/*
 * Virtual key code for number 6 key
 */
#define VK_6			0x36

/*
 * Virtual key code for number 7 key
 */
#define VK_7			0x37

/*
 * Virtual key code for number 8 key
 */
#define VK_8			0x38

/*
 * Virtual key code for number 9 key
 */
#define VK_9			0x39

/* @} */


/*
 * @defgroup VK_Letters Letter Keys (A-Z)
 * @brief Virtual key codes for alphabetic keys
 * @{
 */

/*
 * Virtual key code for letter A key
 */
#define VK_A			0x41

/*
 * Virtual key code for letter B key
 */
#define VK_B			0x42

/*
 * Virtual key code for letter C key
 */
#define VK_C			0x43

/*
 * Virtual key code for letter D key
 */
#define VK_D			0x44

/*
 * Virtual key code for letter E key
 */
#define VK_E			0x45

/*
 * Virtual key code for letter F key
 */
#define VK_F			0x46

/*
 * Virtual key code for letter G key
 */
#define VK_G			0x47

/*
 * Virtual key code for letter H key
 */
#define VK_H			0x48

/*
 * Virtual key code for letter I key
 */
#define VK_I			0x49

/*
 * Virtual key code for letter J key
 */
#define VK_J			0x4A

/*
 * Virtual key code for letter K key
 */
#define VK_K			0x4B

/*
 * Virtual key code for letter L key
 */
#define VK_L			0x4C

/*
 * Virtual key code for letter M key
 */
#define VK_M			0x4D

/*
 * Virtual key code for letter N key
 */
#define VK_N			0x4E

/*
 * Virtual key code for letter O key
 */
#define VK_O			0x4F

/*
 * Virtual key code for letter P key
 */
#define VK_P			0x50

/*
 * Virtual key code for letter Q key
 */
#define VK_Q			0x51

/*
 * Virtual key code for letter R key
 */
#define VK_R			0x52

/*
 * Virtual key code for letter S key
 */
#define VK_S			0x53

/*
 * Virtual key code for letter T key
 */
#define VK_T			0x54

/*
 * Virtual key code for letter U key
 */
#define VK_U			0x55

/*
 * Virtual key code for letter V key
 */
#define VK_V			0x56

/*
 * Virtual key code for letter W key
 */
#define VK_W			0x57

/*
 * Virtual key code for letter X key
 */
#define VK_X			0x58

/*
 * Virtual key code for letter Y key
 */
#define VK_Y			0x59

/*
 * Virtual key code for letter Z key
 */
#define VK_Z			0x5A

/* @} */


/*
 * @defgroup VK_FunctionKeys Function Keys (F1-F24)
 * @brief Virtual key codes for function keys
 * @{
 */

/*
 * Virtual key code for function key F1
 */
#define VK_F1			0x70

/*
 * Virtual key code for function key F2
 */
#define VK_F2			0x71

/*
 * Virtual key code for function key F3
 */
#define VK_F3			0x72

/*
 * Virtual key code for function key F4
 */
#define VK_F4			0x73

/*
 * Virtual key code for function key F5
 */
#define VK_F5			0x74

/*
 * Virtual key code for function key F6
 */
#define VK_F6			0x75

/*
 * Virtual key code for function key F7
 */
#define VK_F7			0x76

/*
 * Virtual key code for function key F8
 */
#define VK_F8			0x77

/*
 * Virtual key code for function key F9
 */
#define VK_F9			0x78

/*
 * Virtual key code for function key F10
 */
#define VK_F10			0x79

/*
 * Virtual key code for function key F11
 */
#define VK_F11			0x7A

/*
 * Virtual key code for function key F12
 */
#define VK_F12			0x7B

/*
 * Virtual key code for function key F13
 */
#define VK_F13			0x7C

/*
 * Virtual key code for function key F14
 */
#define VK_F14			0x7D

/*
 * Virtual key code for function key F15
 */
#define VK_F15			0x7E

/*
 * Virtual key code for function key F16
 */
#define VK_F16			0x7F

/*
 * Virtual key code for function key F17
 */
#define VK_F17			0x80

/*
 * Virtual key code for function key F18
 */
#define VK_F18			0x81

/*
 * Virtual key code for function key F19
 */
#define VK_F19			0x82

/*
 * Virtual key code for function key F20
 */
#define VK_F20			0x83

/*
 * Virtual key code for function key F21
 */
#define VK_F21			0x84

/*
 * Virtual key code for function key F22
 */
#define VK_F22			0x85

/*
 * Virtual key code for function key F23
 */
#define VK_F23			0x86

/*
 * Virtual key code for function key F24
 */
#define VK_F24			0x87

/* @} */


/*
 * @defgroup VK_SpecialKeys Special Keys
 * @brief Virtual key codes for special state keys
 * @{
 */

/*
 * Virtual key code for NUM LOCK key
 * @details State key for the numeric keypad lock
 */
#define VK_NUMLOCK		0x90

/*
 * Virtual key code for SCROLL LOCK key
 * @details State key for scroll lock functionality
 */
#define VK_SCROLL		0x91

/* @} */

/* @} */


/*
 * @defgroup HotKey_Functions HotKey Manipulation Functions
 * @brief Functions to get, set, and clear hotkey values
 * @{
 */

/*
 * @brief Get the current hotkey value from the shell link
 * 
 * @details Retrieves the 16-bit HotKey field value from the ShellLinkHeader.
 * The returned value contains both the modifier keys (high byte) and the
 * virtual key code (low byte).
 * 
 * The hotkey value is constructed as:
 * - High byte (bits 15-8): Modifier keys (combination of VK_M_SHIFT, VK_M_CONTROL, VK_M_ALT)
 * - Low byte (bits 7-0): Virtual key code (e.g., VK_F5, VK_A, VK_1)
 * 
 * Example: A hotkey value of 0x0475 represents Ctrl+F5 (0x04 modifier, 0x75 VK_F5)
 * 
 * @param[in] Link Pointer to MSShellLink structure
 * 
 * @return 16-bit hotkey value (0x0000 if no hotkey is set, or on error)
 *         Returns 0 for both "no hotkey" and error conditions - caller should
 *         validate the link pointer before calling
 * 
 * @see SetHotKey(), ClearHotKey(), [MS-SHLLINK] section 2.1.3
 */
uint16_t GetHotKey(struct MSShellLink *Link);

/*
 * @brief Set a hotkey for the shell link
 * 
 * @details Sets the HotKey field in the ShellLinkHeader to the specified
 * modifier and virtual key combination. This creates a keyboard shortcut
 * that can be used to launch the link target directly.
 * 
 * The hotkey is a 16-bit value constructed as:
 * - High byte (bits 15-8): Modifier keys (combination of VK_M_SHIFT, VK_M_CONTROL, VK_M_ALT)
 * - Low byte (bits 7-0): Virtual key code (e.g., VK_F5, VK_A, VK_1)
 * 
 * Example: SetHotKey(link, VK_M_CONTROL | VK_M_SHIFT, VK_F5) creates Ctrl+Shift+F5
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * @param[in] Modifier Modifier key byte combining zero or more of:
 *            VK_M_NONE, VK_M_SHIFT, VK_M_CONTROL, VK_M_ALT
 * @param[in] VKey Virtual key code byte from VK_* constants
 *            (e.g., VK_0 through VK_9, VK_A through VK_Z, VK_F1 through VK_F24,
 *            VK_NUMLOCK, VK_SCROLL, or VK_NONE)
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see GetHotKey(), ClearHotKey(), [MS-SHLLINK] section 2.1.3
 */
int SetHotKey(struct MSShellLink *Link, uint8_t Modifier, uint8_t VKey);

/*
 * @brief Clear (remove) the hotkey from the shell link
 * 
 * @details Clears the HotKey field in the ShellLinkHeader by setting it to
 * zero (0x0000), effectively removing any keyboard shortcut assigned to
 * the link.
 * 
 * @param[in,out] Link Pointer to MSShellLink structure
 * 
 * @return 0 on success, negative value on error (e.g., NULL pointer)
 * 
 * @see GetHotKey(), SetHotKey(), [MS-SHLLINK] section 2.1.3
 */
int ClearHotKey(struct MSShellLink *Link);

/* @} */

#endif /* HOTKEY_H */
