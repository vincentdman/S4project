/**
 * @file LCD_Commands.h
 * @author Vincent de Man
 * @brief Display commands for 16x2 display.
 * @version 1.1
 * @date 2021-04-01
 * @details Includes most of the lcd function commands to send to the lcd. Data type is binary. 
 * @copyright Copyright (cpp) 2021
 * 
 */
#ifndef LCD_Commands_h
#define LCD_Commands_h

// commands
#define LCD_CLEAR 0b00000001
#define LCD_HOME 0b00000010
#define LCD_CURSOR_DIRECTION_LEFT 0b00000110
#define LCD_CURSOR_DIRECTION_RIGHT 0b00000100
#define LCD_SHIFT_ENTIRE_DISPLAY_RIGHT 0b00000101
#define LCD_SHIFT_ENTIRE_DISPLAY_LEFT 0b00000111
#define LCD_DISPLAY_ON 0b00001100
#define lCD_DISPLAY_OFF 0b00001000
#define LCD_DISPLAY_ON_CURSOR_ON 0b00001110
#define LCD_DISPLAY_ON_CURSOR_OFF 0b00001100
#define LCD_DISPLAY_OFF_CURSOR_ON 0b00001010
#define LCD_DISPLAY_OFF_CURSOR_FF 0b00001000
#define LCD_CURSOR_BLINK_OFF 0b00001110
#define LCD_CURSOR_BLINK_ON 0b00001111
#define LCD_CURSOR_BLINK_ON_CRUSOR_OFF 0b00001101
#define LCD_CURSOR_BLINK_OFF_CURSOR_OFF 0b00001100
#define LCD_4_BIT_MODE 0b00101000
#define LCD_8_BIT_MODE 0b00111000
#define LCD_NEXT_LINE 0b11000000

#endif