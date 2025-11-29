#ifndef HOTKEY_H
#define HOTKEY_H

#include "LibSLNK.h"


// HighByte Modifier
#define VK_M_NONE		0x00
#define VK_M_SHIFT		0x01
#define VK_M_CONTROL	0x02
#define VK_M_ALT		0x04

// LowByte VirtualKey
#define VK_NONE			0x00

#define VK_0			0x30
#define VK_1			0x31
#define VK_2			0x32
#define VK_3			0x33
#define VK_4			0x34
#define VK_5			0x35
#define VK_6			0x36
#define VK_7			0x37
#define VK_8			0x38
#define VK_9			0x39

#define VK_A			0x41
#define VK_B			0x42
#define VK_C			0x43
#define VK_D			0x44
#define VK_E			0x45
#define VK_F			0x46
#define VK_G			0x47
#define VK_H			0x48
#define VK_I			0x49
#define VK_J			0x4A
#define VK_K			0x4B
#define VK_L			0x4C
#define VK_M			0x4D
#define VK_N			0x4E
#define VK_O			0x4F
#define VK_P			0x50
#define VK_Q			0x51
#define VK_R			0x52
#define VK_S			0x53
#define VK_T			0x54
#define VK_U			0x55
#define VK_V			0x56
#define VK_W			0x57
#define VK_X			0x58
#define VK_Y			0x59
#define VK_Z			0x5A

#define VK_F1			0x70
#define VK_F2			0x71
#define VK_F3			0x72
#define VK_F4			0x73
#define VK_F5			0x74
#define VK_F6			0x75
#define VK_F7			0x76
#define VK_F8			0x77
#define VK_F9			0x78
#define VK_F10			0x79
#define VK_F11			0x7A
#define VK_F12			0x7B
#define VK_F13			0x7C
#define VK_F14			0x7D
#define VK_F15			0x7E
#define VK_F16			0x7F
#define VK_F17			0x80
#define VK_F18			0x81
#define VK_F19			0x82
#define VK_F20			0x83
#define VK_F21			0x84
#define VK_F22			0x85
#define VK_F23			0x86
#define VK_F24			0x87

#define VK_NUMLOCK		0x90
#define VK_SCROLL		0x91



int SetHotKey(struct MSShellLink *lnk, uint8_t modifier, uint8_t vkey);
int ClearHotKey(struct MSShellLink *lnk);


#endif /* HOTKEY_H */
