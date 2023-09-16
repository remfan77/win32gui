#pragma once

#include <windows.h>

extern HFONT hf;
extern HWND hWnd;

int create_main_win(int size_x, int size_y);
void main_loop(void);
