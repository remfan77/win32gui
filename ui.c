#include <windows.h>
#include "ui.h"
#include "p1.h"

struct DIALOG dialog[N_MAX];
int N;

int BUTTON_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_PUSHLIKE , x0, y0, size_x, size_y, hWnd, (HMENU)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_BUTTON;
        SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

void BUTTON_DEF_ON_CLICK(int i, void *fn)
{
	dialog[i].fn = fn;
}

int EDIT_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("EDIT", text, WS_VISIBLE | WS_CHILD | WS_BORDER , x0, y0, size_x, size_y, hWnd, (HMENU)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_EDITBOX;
        SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

void EDITBOX_DEF_ON_CHANGE(int i, void *fn)
{
	dialog[i].fn = fn;
}

void EDIT_SET_TEXT(int i, char *text)
{
	SetWindowText(dialog[i].hwnd, text);
}

int CHECKBOX_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX , x0, y0, size_x, size_y, hWnd, (HMENU)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_CHECKBOX;
        SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

void CHECKBOX_DEF_ON_CLICK(int i, void *fn)
{
	dialog[i].fn = fn;
}


