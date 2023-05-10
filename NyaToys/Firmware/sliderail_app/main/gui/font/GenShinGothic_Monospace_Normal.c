/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef GENSHINGOTHIC_MONOSPACE_NORMAL
#define GENSHINGOTHIC_MONOSPACE_NORMAL 1
#endif

#if GENSHINGOTHIC_MONOSPACE_NORMAL

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xaa, 0xaa, 0xf,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x14, 0x28, 0x93, 0xf2, 0x44, 0x89, 0x7f, 0x28,
    0x50, 0xa2, 0x40,

    /* U+0024 "$" */
    0x20, 0x87, 0xb3, 0x82, 0xc, 0x1c, 0x18, 0x30,
    0x41, 0x8f, 0xe2, 0x8,

    /* U+0025 "%" */
    0x60, 0x91, 0x92, 0x94, 0x90, 0x60, 0x6, 0x29,
    0x29, 0x49, 0x89, 0x6,

    /* U+0026 "&" */
    0x30, 0x91, 0x22, 0x45, 0x4, 0x18, 0xd9, 0x9d,
    0x1b, 0x3b, 0x90,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x88, 0x44, 0x21,

    /* U+0029 ")" */
    0x84, 0x22, 0x11, 0x11, 0x11, 0x12, 0x22, 0x48,

    /* U+002A "*" */
    0x21, 0x3e, 0xe5, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8,

    /* U+002C "," */
    0x6c, 0xa4,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x10, 0x82, 0x8, 0x41, 0x4, 0x20, 0x82,
    0x10, 0x41, 0x8, 0x20,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x86, 0x14,
    0x8c,

    /* U+0031 "1" */
    0x31, 0xc1, 0x4, 0x10, 0x41, 0x4, 0x10, 0x41,
    0x3f,

    /* U+0032 "2" */
    0x7b, 0x30, 0x41, 0x4, 0x30, 0x86, 0x30, 0x84,
    0x3f,

    /* U+0033 "3" */
    0x39, 0x10, 0x41, 0xc, 0xe0, 0xc1, 0x4, 0x1c,
    0xde,

    /* U+0034 "4" */
    0x18, 0x30, 0x61, 0x42, 0x89, 0x12, 0x44, 0xfe,
    0x10, 0x20, 0x40,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0x41, 0xe4, 0xc1, 0x4, 0x18,
    0x9e,

    /* U+0036 "6" */
    0x39, 0x14, 0x20, 0x82, 0xec, 0xe1, 0x86, 0x14,
    0xce,

    /* U+0037 "7" */
    0xfc, 0x30, 0x86, 0x10, 0x42, 0x8, 0x20, 0x82,
    0x8,

    /* U+0038 "8" */
    0x39, 0x14, 0x51, 0x64, 0xe5, 0xa3, 0x86, 0x1c,
    0xde,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0x87, 0x37, 0x41, 0x4, 0x28,
    0x9c,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0x3, 0xde,

    /* U+003C "<" */
    0x6, 0x73, 0x7, 0x3, 0x80, 0xc0,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0xc0, 0x70, 0x18, 0x33, 0x98, 0x0,

    /* U+003F "?" */
    0x39, 0x10, 0x41, 0x8, 0x61, 0xc, 0x0, 0x3,
    0xc,

    /* U+0040 "@" */
    0x3c, 0xc9, 0xc, 0x18, 0x33, 0xec, 0xd1, 0xa7,
    0x36, 0x2, 0x6, 0x7, 0x80,

    /* U+0041 "A" */
    0x18, 0x18, 0x18, 0x2c, 0x24, 0x24, 0x24, 0x7e,
    0x42, 0x42, 0x42, 0xc3,

    /* U+0042 "B" */
    0xf2, 0x28, 0xa2, 0x9b, 0xc8, 0xa1, 0x86, 0x18,
    0xfc,

    /* U+0043 "C" */
    0x39, 0x14, 0x20, 0x82, 0x8, 0x20, 0x81, 0x4,
    0x4e,

    /* U+0044 "D" */
    0xf2, 0x68, 0xa1, 0x86, 0x18, 0x61, 0x86, 0x29,
    0xbc,

    /* U+0045 "E" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x84, 0x21, 0xf0,

    /* U+0046 "F" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x84, 0x21, 0x0,

    /* U+0047 "G" */
    0x39, 0x14, 0x20, 0x82, 0x9, 0xe1, 0x85, 0x14,
    0x4e,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0x87, 0xf8, 0x61, 0x86, 0x18,
    0x61,

    /* U+0049 "I" */
    0xfc, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82,
    0x3f,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0x66, 0xe0,

    /* U+004B "K" */
    0x8e, 0x29, 0x24, 0xa3, 0xcd, 0x24, 0x8a, 0x28,
    0xe1,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0x84, 0x21, 0xf0,

    /* U+004D "M" */
    0xc7, 0x3c, 0xf3, 0xd6, 0xdb, 0x6d, 0x86, 0x18,
    0x61,

    /* U+004E "N" */
    0xc7, 0x1c, 0x69, 0xa6, 0x99, 0x65, 0x96, 0x38,
    0xe3,

    /* U+004F "O" */
    0x38, 0x8b, 0x1c, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x89, 0x11, 0xc0,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x86, 0x2f, 0x20, 0x82, 0x8,
    0x20,

    /* U+0051 "Q" */
    0x38, 0x8b, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xe1, 0x3, 0x3, 0x80,

    /* U+0052 "R" */
    0xfa, 0x38, 0x61, 0x86, 0x3f, 0xa4, 0x9a, 0x28,
    0xe1,

    /* U+0053 "S" */
    0x7a, 0x38, 0x20, 0xc1, 0xc1, 0x83, 0x4, 0x18,
    0xde,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x86, 0x1c,
    0xde,

    /* U+0056 "V" */
    0x42, 0x42, 0x42, 0x66, 0x66, 0x24, 0x24, 0x24,
    0x3c, 0x18, 0x18, 0x18,

    /* U+0057 "W" */
    0x81, 0x81, 0x83, 0xda, 0xda, 0x5a, 0x5a, 0x6a,
    0x6a, 0x66, 0x66, 0x66,

    /* U+0058 "X" */
    0x87, 0x34, 0x92, 0x30, 0xc3, 0x1c, 0x49, 0x2c,
    0xe1,

    /* U+0059 "Y" */
    0xc6, 0x89, 0x13, 0x62, 0x85, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+005A "Z" */
    0xfc, 0x30, 0x86, 0x10, 0xc2, 0x8, 0x41, 0x8,
    0x3f,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+005C "\\" */
    0x82, 0x4, 0x10, 0x40, 0x82, 0x8, 0x10, 0x41,
    0x2, 0x8, 0x20, 0x41,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+005E "^" */
    0x30, 0xc3, 0x12, 0x4b, 0x38, 0x40,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xc8, 0x80,

    /* U+0061 "a" */
    0x7a, 0x30, 0x43, 0x76, 0x18, 0x63, 0x74,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xca, 0x18, 0x61, 0x86, 0x18,
    0xbc,

    /* U+0063 "c" */
    0x39, 0x8, 0x20, 0x82, 0x8, 0x11, 0x38,

    /* U+0064 "d" */
    0x4, 0x10, 0x4f, 0x46, 0x18, 0x61, 0x86, 0x14,
    0xdd,

    /* U+0065 "e" */
    0x39, 0x28, 0x61, 0xfe, 0x8, 0x10, 0x38,

    /* U+0066 "f" */
    0x1e, 0x40, 0x87, 0xe2, 0x4, 0x8, 0x10, 0x20,
    0x40, 0x81, 0x0,

    /* U+0067 "g" */
    0x7f, 0xa, 0x14, 0x27, 0x90, 0x20, 0x40, 0x7d,
    0x6, 0x1b, 0xe0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x61,

    /* U+0069 "i" */
    0x18, 0xc1, 0xf0, 0x84, 0x21, 0x8, 0x42, 0x10,

    /* U+006A "j" */
    0x18, 0xc1, 0xf0, 0x84, 0x21, 0x8, 0x42, 0x10,
    0x8f, 0xc0,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x9a, 0x4a, 0x3c, 0xd2, 0x68,
    0xa3,

    /* U+006C "l" */
    0xe0, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82,
    0x7,

    /* U+006D "m" */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x92,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61, 0x84,

    /* U+006F "o" */
    0x71, 0x28, 0x61, 0x86, 0x18, 0x52, 0x70,

    /* U+0070 "p" */
    0xbb, 0x28, 0x61, 0x86, 0x18, 0x62, 0xf2, 0x8,
    0x20,

    /* U+0071 "q" */
    0x3d, 0x18, 0x61, 0x86, 0x18, 0x53, 0x74, 0x10,
    0x41,

    /* U+0072 "r" */
    0xbe, 0x21, 0x8, 0x42, 0x10, 0x80,

    /* U+0073 "s" */
    0x7a, 0x8, 0x30, 0x38, 0x30, 0x61, 0x78,

    /* U+0074 "t" */
    0x20, 0x82, 0x3f, 0x20, 0x82, 0x8, 0x20, 0x82,
    0x7,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x63, 0x74,

    /* U+0076 "v" */
    0x86, 0x1c, 0xd2, 0x49, 0x27, 0x8c, 0x30,

    /* U+0077 "w" */
    0x81, 0x99, 0xdb, 0x5a, 0x5a, 0x6a, 0x6a, 0x66,
    0x66,

    /* U+0078 "x" */
    0xc5, 0x24, 0x8c, 0x30, 0xc4, 0xb2, 0x84,

    /* U+0079 "y" */
    0x86, 0x1c, 0xd2, 0x49, 0xa3, 0x8c, 0x30, 0xc2,
    0x30,

    /* U+007A "z" */
    0xfc, 0x21, 0x84, 0x20, 0x84, 0x10, 0xfc,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x10, 0x84, 0xc1, 0x8, 0x42,
    0x10, 0x87,

    /* U+007C "|" */
    0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x84, 0x19, 0x8, 0x42,
    0x10, 0x98,

    /* U+007E "~" */
    0x70, 0x5a, 0xe,

    /* U+4F7F "使" */
    0x10, 0x80, 0x7f, 0xf2, 0x8, 0x18, 0x20, 0x6f,
    0xfa, 0xa2, 0x22, 0x88, 0x8b, 0xfe, 0x20, 0x80,
    0x92, 0x2, 0x28, 0x8, 0x60, 0x26, 0x70, 0xa0,
    0x70,

    /* U+505C "停" */
    0x10, 0x80, 0x7f, 0xf2, 0x0, 0x9, 0xfe, 0x64,
    0xa, 0x9f, 0xea, 0x0, 0xb, 0xff, 0x28, 0x4,
    0xbf, 0xf2, 0x8, 0x8, 0x20, 0x20, 0x80, 0x8e,
    0x0,

    /* U+5173 "关" */
    0x0, 0x4, 0x10, 0xc2, 0x8, 0x87, 0xfc, 0x8,
    0x1, 0x0, 0x20, 0xff, 0xe0, 0x80, 0x38, 0x5,
    0x1, 0x10, 0xc1, 0xb0, 0x18,

    /* U+53CD "反" */
    0x3f, 0xfc, 0x80, 0x2, 0x0, 0x8, 0x0, 0x20,
    0x0, 0xff, 0xe2, 0x81, 0x9, 0x4, 0x24, 0x20,
    0x89, 0x82, 0x1c, 0x10, 0x60, 0x47, 0x63, 0x70,
    0x70, 0x0, 0x40,

    /* U+540D "名" */
    0x2, 0x0, 0x10, 0x0, 0xff, 0x2, 0x8, 0x30,
    0x21, 0xa1, 0x4, 0x48, 0x0, 0xe0, 0x3, 0x0,
    0x1f, 0xf1, 0xc0, 0x79, 0x1, 0x4, 0x4, 0x10,
    0x10, 0x7f, 0xc0,

    /* U+5728 "在" */
    0x0, 0x0, 0x10, 0x0, 0x40, 0x3f, 0xff, 0x8,
    0x0, 0x41, 0x3, 0x4, 0x8, 0x10, 0x67, 0xfa,
    0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0xff, 0xc0,

    /* U+5931 "失" */
    0x12, 0x0, 0x48, 0x2, 0x20, 0xf, 0xfe, 0x42,
    0x3, 0x8, 0x0, 0x20, 0x3f, 0xff, 0x3, 0x0,
    0x1e, 0x0, 0x48, 0x2, 0x10, 0x30, 0x33, 0x80,
    0x70,

    /* U+5EA6 "度" */
    0x1, 0x1, 0xff, 0xf4, 0x0, 0x11, 0x8, 0x5f,
    0xfd, 0x10, 0x84, 0x42, 0x11, 0xf8, 0x40, 0x1,
    0x7f, 0xe4, 0x43, 0x30, 0x98, 0x81, 0xc2, 0x79,
    0xe8, 0x0, 0x40,

    /* U+5F0F "式" */
    0x0, 0xb0, 0x2, 0x60, 0x8, 0xbf, 0xff, 0x0,
    0x80, 0x3, 0x7, 0xfc, 0x4, 0x10, 0x10, 0x40,
    0x41, 0x1, 0x6, 0x45, 0xc9, 0xf8, 0x36, 0x0,
    0x70,

    /* U+673A "机" */
    0x11, 0xf0, 0x22, 0x20, 0x44, 0x47, 0xe8, 0x83,
    0x11, 0x6, 0x22, 0xe, 0x44, 0x2c, 0x88, 0x55,
    0x11, 0x22, 0x22, 0x48, 0x48, 0x90, 0x91, 0x61,
    0x22, 0x83, 0xc0,

    /* U+6A21 "模" */
    0x21, 0x10, 0x4f, 0xf8, 0x84, 0x47, 0xdf, 0xc3,
    0x40, 0x86, 0x7f, 0x1b, 0x2, 0x35, 0xfc, 0xa0,
    0x41, 0x41, 0x82, 0x9f, 0xf1, 0x5, 0x2, 0x11,
    0x4, 0xc1, 0x80,

    /* U+6B21 "次" */
    0x1, 0x0, 0x82, 0x0, 0xc8, 0x0, 0xdf, 0xf0,
    0x24, 0x40, 0x88, 0x83, 0x11, 0x0, 0x20, 0x18,
    0xc0, 0x61, 0x41, 0x82, 0x82, 0x8, 0x80, 0x20,
    0x81, 0x80, 0xc0, 0x0, 0x80,

    /* U+6B62 "止" */
    0x1, 0x0, 0x4, 0x0, 0x10, 0x8, 0x40, 0x21,
    0x0, 0x87, 0xe2, 0x10, 0x8, 0x40, 0x21, 0x0,
    0x84, 0x2, 0x10, 0x8, 0x40, 0xff, 0xfc,

    /* U+6B63 "正" */
    0x7f, 0xfc, 0x4, 0x0, 0x10, 0x8, 0x40, 0x21,
    0x0, 0x87, 0xe2, 0x10, 0x8, 0x40, 0x21, 0x0,
    0x84, 0x2, 0x10, 0x3f, 0xff,

    /* U+6B65 "步" */
    0x1, 0x0, 0x84, 0x2, 0x1f, 0x88, 0x40, 0x21,
    0x3, 0xff, 0xf0, 0x10, 0x4, 0x44, 0x21, 0x13,
    0x4, 0x80, 0x66, 0x0, 0x30, 0x3, 0x80, 0x78,
    0x2, 0x0, 0x0,

    /* U+72B6 "状" */
    0x10, 0x80, 0x42, 0x49, 0x8, 0x94, 0x20, 0x17,
    0xfc, 0x42, 0x1, 0xc, 0xc, 0x70, 0x51, 0x42,
    0x44, 0x81, 0x32, 0x4, 0x84, 0x14, 0x18, 0x60,
    0x30,

    /* U+786E "确" */
    0x0, 0xc3, 0xf2, 0x2, 0xf, 0x8, 0x64, 0x21,
    0x31, 0xf, 0xf7, 0x92, 0x52, 0x7f, 0xc9, 0x27,
    0x24, 0x94, 0x9f, 0xd2, 0xc1, 0x7a, 0x5, 0x8,
    0x10, 0x41, 0xc0,

    /* U+79F0 "称" */
    0x1c, 0x83, 0xc6, 0x1, 0x1f, 0xc4, 0x48, 0xfe,
    0x20, 0xd8, 0x83, 0xa, 0x96, 0x49, 0x55, 0x26,
    0x44, 0x99, 0x22, 0x44, 0x8, 0x10, 0x20, 0x43,
    0x80,

    /* U+80FD "能" */
    0x10, 0x40, 0x48, 0x98, 0x89, 0xc7, 0xfa, 0x0,
    0x14, 0x20, 0x8, 0x5f, 0x9f, 0x21, 0x20, 0x7e,
    0x44, 0x84, 0xf1, 0xf9, 0x2, 0x12, 0x14, 0x24,
    0x29, 0xcf, 0xc0,

    /* U+884C "行" */
    0x8, 0x0, 0x23, 0xfc, 0xc0, 0x3, 0x0, 0x0,
    0xc0, 0x1, 0x0, 0x4, 0xff, 0x98, 0xc, 0x50,
    0x18, 0x20, 0x30, 0x40, 0x60, 0x80, 0xc1, 0x1,
    0x82, 0x3, 0x4, 0x1c, 0x0,

    /* U+89D2 "角" */
    0x6, 0x0, 0x1f, 0x80, 0x86, 0x4, 0x10, 0x3f,
    0xfd, 0x42, 0x11, 0x8, 0x47, 0xff, 0x10, 0x84,
    0x42, 0x11, 0x8, 0x4f, 0xff, 0x20, 0x5, 0x80,
    0x14, 0x3, 0xc0,

    /* U+8FD0 "运" */
    0x40, 0x1, 0x9f, 0xe1, 0x0, 0x0, 0x0, 0xc0,
    0x0, 0xbf, 0xf0, 0x10, 0x0, 0x48, 0xe3, 0x10,
    0x88, 0x62, 0x21, 0x8b, 0xfb, 0x20, 0x3, 0x60,
    0x8, 0xff, 0xc0,

    /* U+901F "速" */
    0x80, 0x81, 0x3f, 0xf2, 0x8, 0x0, 0x20, 0x7,
    0xf8, 0x12, 0x2e, 0x48, 0x89, 0xfe, 0x21, 0xc0,
    0x8a, 0xc2, 0x48, 0x9a, 0x21, 0xd8, 0x2, 0x1f,
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 128, .box_w = 1, .box_h = 4, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 53, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 61, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 73, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 80, .adv_w = 128, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 82, .adv_w = 128, .box_w = 5, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 83, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 96, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 128, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 128, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 194, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 200, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 205, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 211, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 233, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 128, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 392, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 491, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 503, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 511, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 517, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 518, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 520, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 581, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 128, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 608, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 657, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 666, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 727, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 128, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 744, .adv_w = 128, .box_w = 1, .box_h = 18, .ofs_x = 4, .ofs_y = -5},
    {.bitmap_index = 747, .adv_w = 128, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 757, .adv_w = 128, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 760, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 785, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 810, .adv_w = 256, .box_w = 11, .box_h = 15, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 831, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 858, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 885, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 912, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 937, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 964, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 989, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1016, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1043, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1072, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 256, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1116, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1143, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1168, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1195, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1220, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1247, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1276, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1303, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1330, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0xdd, 0x1f4, 0x44e, 0x48e, 0x7a9, 0x9b2, 0xf27,
    0xf90, 0x17bb, 0x1aa2, 0x1ba2, 0x1be3, 0x1be4, 0x1be6, 0x2337,
    0x28ef, 0x2a71, 0x317e, 0x38cd, 0x3a53, 0x4051, 0x40a0
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 20351, .range_length = 16545, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 23, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 0, 0, 0, 3, 4, 3,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 6, 6, 0, 0, 0,
    0, 0, 7, 8, 9, 10, 0, 11,
    12, 0, 0, 13, 14, 15, 0, 0,
    10, 16, 10, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 2, 26, 0, 0,
    0, 0, 27, 28, 29, 0, 30, 31,
    32, 33, 0, 0, 34, 0, 33, 33,
    28, 28, 35, 36, 37, 38, 35, 39,
    40, 41, 42, 43, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 0, 0, 0,
    2, 0, 3, 4, 0, 5, 6, 5,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 8, 0, 0, 0,
    9, 0, 10, 0, 11, 0, 0, 0,
    11, 0, 0, 12, 0, 0, 0, 0,
    11, 0, 11, 0, 13, 14, 15, 16,
    17, 18, 19, 20, 0, 21, 3, 0,
    0, 0, 22, 0, 23, 23, 23, 24,
    25, 0, 26, 27, 0, 0, 28, 28,
    23, 28, 23, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, -29, 0, 0, 0,
    0, -14, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 21, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -24, 0, -35, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -27, -5, -18,
    -9, 0, -23, 0, 0, 0, -2, 0,
    0, 0, 7, 0, 0, -7, 0, -9,
    -6, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, -7, -1, -7, -17, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, -20, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, -8, 0,
    -2, 7, 7, 0, 0, 2, -5, 0,
    0, 0, 0, 0, 0, 0, 0, -12,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -13, 0, -24, 0, 0, 0, 0,
    -7, 0, -2, 0, 0, -10, -4, -3,
    0, 1, -3, -2, -10, 0, 0, -2,
    0, 0, 0, 0, 0, -3, -1, -3,
    -1, 0, -3, 0, 0, 0, 0, -8,
    0, 0, 0, 0, 0, 0, 0, -4,
    -3, -6, 0, -1, -1, -1, -3, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -3, -2, -2, -3, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, -7, -2, -6, -4, -3, -1,
    -1, -1, -2, -2, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, -3, -2, -3,
    -2, 0, -3, 0, 0, 0, 0, -9,
    0, 0, -3, 0, 0, -2, 0, -10,
    0, -5, 0, -2, -1, -4, -5, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, -18, 0, -18, 0,
    0, -9, -2, -35, -5, 0, 0, 1,
    1, -6, 0, -8, 0, -9, -3, 0,
    -6, 0, 0, -5, -5, -2, -4, -5,
    -4, -7, -4, -8, 0, 0, 0, -7,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, -5, 0, -3, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, 0, 0,
    0, 0, 0, -10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -5,
    0, -8, 0, 0, -2, -2, -6, 0,
    -3, -4, -3, -3, -2, 0, -4, 0,
    0, 0, -2, 0, 0, 0, -2, 0,
    0, -7, -3, -5, -4, -4, -5, -3,
    0, -23, 0, -39, 0, -14, 0, 0,
    -8, 1, -7, 0, -6, -31, -7, -19,
    -14, 0, -19, 0, -20, 0, -3, -3,
    -1, 0, 0, 0, 0, -5, -2, -9,
    -9, 0, -9, 0, 0, 0, 0, 0,
    -29, -6, -19, 0, 0, -13, 0, -37,
    -2, -6, 0, 0, 0, -6, -2, -20,
    0, -11, -6, 0, -8, 0, 0, 0,
    -2, 0, 0, 0, 0, -3, 0, -5,
    0, 0, 0, -2, 0, -10, 0, 0,
    0, -2, 0, -4, -3, -5, 0, -3,
    0, -2, -3, -2, 0, -2, -2, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -3, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, -3,
    -3, -5, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -27, -20, -23, 0,
    0, -10, -6, -32, -10, 0, 0, 0,
    0, -5, -3, -14, 0, -19, -17, -4,
    -19, 0, 0, -12, -15, -4, -12, -8,
    -9, -10, -8, -19, 0, 0, 0, 0,
    -4, 0, -8, 0, 0, -4, 0, -12,
    -2, 0, 0, -2, 0, -2, -3, 0,
    0, -1, 0, 0, -2, 0, 0, 0,
    -1, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, -17, -5, -12, 0,
    0, -3, -2, -19, -4, 0, -2, 0,
    0, 0, 0, -5, 0, -6, -4, 0,
    -5, -1, 0, -5, -3, 0, -8, -2,
    -2, -4, -2, -6, 0, 0, 0, 0,
    -9, -1, -7, 0, 0, 0, -1, -17,
    -1, 0, 0, 0, 0, 0, 0, -1,
    0, -4, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -1, 0, -2, 0, -7, 0, 0,
    0, 1, -4, -1, -3, -5, -2, 0,
    0, 0, 0, 0, 0, -2, -2, -4,
    0, 0, 0, 0, 0, -4, -2, -4,
    -3, -2, -4, -3, 0, 0, 0, 0,
    -23, -17, -17, -6, -2, -3, -3, -25,
    -4, -3, -2, 0, 0, 0, 0, -7,
    0, -17, -10, 0, -15, 0, 0, -10,
    -10, -3, -9, -3, -6, -9, -3, -12,
    0, 0, 0, 0, 0, -9, 0, 0,
    0, -1, -5, -8, -8, 0, -2, -1,
    -1, 0, -3, -2, 0, -4, -5, -5,
    -3, 0, 0, 0, 0, -3, -6, -4,
    -4, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -22, -7, -13, -6, 0, -19, 0,
    0, 0, 0, 0, 9, 0, 19, 0,
    0, 0, 0, -5, -1, 0, 3, 0,
    0, 0, 0, -14, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, -6, 0, -4,
    -1, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 2, 0, 0, -3, 0, 0, 0,
    0, -14, 0, -5, 0, -1, -12, 0,
    -7, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -1, -4, -1, -1,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -3,
    0, 0, -6, 0, 0, -2, -5, 0,
    -2, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 2, 0, 0, 0, 0, -9,
    0, 2, 0, 0, -2, 0, 0, -5,
    -5, -6, 0, -4, -2, 0, -7, 0,
    -5, -3, 0, 0, -2, 0, 0, 0,
    0, -3, 0, 1, 1, -2, 1, 1,
    4, 10, 13, 0, -13, -3, -3, 0,
    7, 0, 0, 0, 0, 12, 0, 14,
    12, 9, 12, 0, 16, -5, -2, 0,
    -3, 0, -2, 0, -1, 0, -4, 3,
    0, -1, 0, -3, 0, 0, 4, -9,
    0, 0, 12, 0, -9, 0, 0, 0,
    0, -7, 0, 0, 0, 0, -3, 0,
    0, -4, -3, 0, 0, 0, 10, 0,
    0, 0, 0, -1, -1, 0, -1, -3,
    0, 0, 0, -9, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, -6, 0, -2,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    4, -11, 0, 0, -3, 0, 0, 0,
    0, -6, 0, 0, 0, 0, -3, 0,
    0, -2, -4, 0, -2, 0, -2, 0,
    0, -3, -3, 0, 0, -1, 0, -2,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -3,
    0, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, -6, -9, 0, 0, -5, 0, -14,
    0, 0, 0, 0, 0, 0, 0, -2,
    3, -6, -2, 0, -2, 0, -1, 0,
    -2, 0, 0, 5, 3, 0, 5, -2,
    0, 0, 0, -12, 0, 3, 0, 0,
    -3, 0, 0, 0, 0, -6, 0, -2,
    0, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    4, -7, 4, 4, -7, 0, 0, 0,
    0, -3, 0, 0, 0, 0, -1, 0,
    0, -4, -2, 0, -2, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -9, -2, -5, 0,
    0, -3, 0, -10, 0, -5, 0, -1,
    0, 0, -2, -1, 0, -5, -1, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, -2,
    -10, 0, -2, 0, 0, -1, 0, -8,
    0, -6, 0, -1, 0, -3, -3, 0,
    0, -2, -1, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, -4, 0, -3, 0, 0,
    0, 0, -2, 0, -1, -8, 0, -2,
    0, -2, -4, 0, 0, -2, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    -9, 0, -3, 0, 0, 0, 0, -10,
    0, -5, 0, -1, 0, -1, -2, 0,
    0, -5, -1, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, -1, 0, 0, -6, -2, 0,
    -1, 0, 0, 0, 0, 0, -2, -1,
    0, 0, -1, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 43,
    .right_class_cnt     = 36,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t GenShinGothic_Monospace_Normal = {
#else
lv_font_t GenShinGothic_Monospace_Normal = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if GENSHINGOTHIC_MONOSPACE_NORMAL*/

