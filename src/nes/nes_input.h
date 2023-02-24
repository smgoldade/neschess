// Author: Steven Goldade
#ifndef _NES_INPUT_H_
#define _NES_INPUT_H_
#include "../core.h"
/**
 * @return the currently held buttons on controller 1
 */
extern u8 __fastcall__ input_c1_held();
/**
 * @return the just pressed buttons on controller 1
 */
extern u8 __fastcall__  input_c1_pressed();
/**
 * @return the just released buttons on controller 1
 */
extern u8 __fastcall__ input_c1_released();
/**
 * @return the currently held buttons on controller 2
 */
extern u8 __fastcall__ input_c2_held();
/**
 * @return the just pressed buttons on controller 2
 */
extern u8 __fastcall__ input_c2_pressed();
/**
 * @return the just released buttons on controller 2
 */
extern u8 __fastcall__ input_c2_released();

#define BUTTON_RIGHT(x) BIT_CHECK_0(x)
#define BUTTON_LEFT(x) BIT_CHECK_1(x)
#define BUTTON_DOWN(x) BIT_CHECK_2(x)
#define BUTTON_UP(x) BIT_CHECK_3(x)
#define BUTTON_START(x) BIT_CHECK_4(x)
#define BUTTON_SELECT(x) BIT_CHECK_5(x)
#define BUTTON_B(x) BIT_CHECK_6(x)
#define BUTTON_A(x) BIT_CHECK_7(x)

#endif //_NES_INPUT_H_