// Author: Steven Goldade
// Contains common core bit math definitions in a way that compiles optimally
#ifndef _BITMATH_H_
#define _BITMATH_H_

#define BIT_CHECK_0(x) (x & 0x1)
#define BIT_CHECK_1(x) (x & 0x2)
#define BIT_CHECK_2(x) (x & 0x4)
#define BIT_CHECK_3(x) (x & 0x8)
#define BIT_CHECK_4(x) (x & 0x10)
#define BIT_CHECK_5(x) (x & 0x20)
#define BIT_CHECK_6(x) (x & 0x40)
#define BIT_CHECK_7(x) (x & 0x80)

#define BIT_CLEAR_0(x) (x = (x & 0xFE))
#define BIT_CLEAR_1(x) (x = (x & 0xFD))
#define BIT_CLEAR_2(x) (x = (x & 0xFB))
#define BIT_CLEAR_3(x) (x = (x & 0xF7))
#define BIT_CLEAR_4(x) (x = (x & 0xEF))
#define BIT_CLEAR_5(x) (x = (x & 0xDF))
#define BIT_CLEAR_6(x) (x = (x & 0xBF))
#define BIT_CLEAR_7(x) (x = (x & 0x7F))
#define BIT_CLEAR_0_2(x) (x = (x & 0xFC))
#define BIT_CLEAR_2_2(x) (x = (x & 0xF3))
#define BIT_CLEAR_4_2(x) (x = (x & 0xCF))
#define BIT_CLEAR_6_2(x) (x = (x & 0x3F))

#define BIT_SET_0(x) (x = (x | 0x1))
#define BIT_SET_1(x) (x = (x | 0x2))
#define BIT_SET_2(x) (x = (x | 0x4))
#define BIT_SET_3(x) (x = (x | 0x8))
#define BIT_SET_4(x) (x = (x | 0x10))
#define BIT_SET_5(x) (x = (x | 0x20))
#define BIT_SET_6(x) (x = (x | 0x40))
#define BIT_SET_7(x) (x = (x | 0x80))
#define BIT_SET_0_2(x) (x = (x | 0x3))
#define BIT_SET_2_2(x) (x = (x | 0xC))
#define BIT_SET_4_2(x) (x = (x | 0x30))
#define BIT_SET_6_2(x) (x = (x | 0xC0))

#define BIT_WRITE_0(x,y) (y ? BIT_SET_0(x) : BIT_CLEAR_0(x))
#define BIT_WRITE_1(x,y) (y ? BIT_SET_1(x) : BIT_CLEAR_1(x))
#define BIT_WRITE_2(x,y) (y ? BIT_SET_2(x) : BIT_CLEAR_2(x))
#define BIT_WRITE_3(x,y) (y ? BIT_SET_3(x) : BIT_CLEAR_3(x))
#define BIT_WRITE_4(x,y) (y ? BIT_SET_4(x) : BIT_CLEAR_4(x))
#define BIT_WRITE_5(x,y) (y ? BIT_SET_5(x) : BIT_CLEAR_5(x))
#define BIT_WRITE_6(x,y) (y ? BIT_SET_6(x) : BIT_CLEAR_6(x))
#define BIT_WRITE_7(x,y) (y ? BIT_SET_7(x) : BIT_CLEAR_7(x))
#define BIT_WRITE_0_2(x,y) ((y == 0) ? BIT_CLEAR_0_2(x) : ((y == 1) ? BIT_SET_0(x) : ((y == 2) ? BIT_SET_1(x) : BIT_SET_0_2(x))))
#define BIT_WRITE_2_2(x,y) ((y == 0) ? BIT_CLEAR_2_2(x) : ((y == 1) ? BIT_SET_2(x) : ((y == 2) ? BIT_SET_3(x) : BIT_SET_2_2(x))))
#define BIT_WRITE_4_2(x,y) ((y == 0) ? BIT_CLEAR_4_2(x) : ((y == 1) ? BIT_SET_4(x) : ((y == 2) ? BIT_SET_5(x) : BIT_SET_4_2(x))))
#define BIT_WRITE_6_2(x,y) ((y == 0) ? BIT_CLEAR_6_2(x) : ((y == 1) ? BIT_SET_6(x) : ((y == 2) ? BIT_SET_7(x) : BIT_SET_6_2(x))))

#endif //_BITMATH_H_