#ifndef _VISUX_KEYBOARD_H
#define  _VISUX_KEYBOARD_H
enum KeyCode
{
    KEY_A = 0x1E,
    KEY_B = 0x30,
    KEY_C = 0x2E,
    KEY_D = 0x20,
};
void InitlizeKeyboard();
void KeyboardInterruptHandler();

#endif