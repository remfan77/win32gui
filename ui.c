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

void ENABLE_WIDGET(int i, int state)
{
	EnableWindow(dialog[i].hwnd, state);
}

void RO_WIDGET(int i, int state)
{
	    SendMessage(dialog[i].hwnd,  EM_SETREADONLY, state, 0);
}

int COMBOBOX_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("COMBOBOX", text, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_TABSTOP , x0, y0, size_x, size_y, hWnd, (HMENU)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_COMBOBOX;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

int COMBOBOX_ADD(int i, char *item)
{
	return SendMessage(dialog[i].hwnd, CB_ADDSTRING, 0, (LPARAM) item);
}

int COMBOBOX_SELECT(int i, int item)
{
	return SendMessage(dialog[i].hwnd, CB_SETCURSEL, 0, (LPARAM) item);
}

int EDITBOX_MULTILINE_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("EDIT", text, WS_VSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY , x0, y0, size_x, size_y, hWnd, (HMENU)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_EDIT_MULTILINE;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

void EDITBOX_MULTILINE_APPEND_TEXT( int i, char *newText )
{
    SendMessageA(dialog[i].hwnd, EM_SETSEL, 0, -1); //Select all
    SendMessageA(dialog[i].hwnd, EM_SETSEL, -1, -1);//Unselect and stay at the end pos
    SendMessageA(dialog[i].hwnd, EM_REPLACESEL, 0, (LPARAM)(newText)); //append text to current pos and scroll down
}
