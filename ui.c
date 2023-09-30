#include <windows.h>
#include "ui.h"
#include "p1.h"

struct DIALOG dialog[N_MAX];
int N;

int BUTTON_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
	dialog[N].hwnd = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_PUSHLIKE , x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
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
	dialog[N].hwnd = CreateWindow("EDIT", text, WS_VISIBLE | WS_CHILD | WS_BORDER , x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
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
	dialog[N].hwnd = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX , x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_CHECKBOX;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

void CHECKBOX_DEF_ON_CLICK(int i, void *fn)
{
	dialog[i].fn = fn;
}

int IS_CHECKBOX_CHECKED(int i)
{
	printf("IsDlgButtonChecked=%d\n", IsDlgButtonChecked(hWnd, i));
	switch (IsDlgButtonChecked(hWnd, i))
	{
		case BST_CHECKED:
			return 1;
		case BST_UNCHECKED:
		 	return 0;
		default:
		case BST_INDETERMINATE:
			return 2;
	}
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
	dialog[N].hwnd = CreateWindow("COMBOBOX", text, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_TABSTOP , x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
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

void COMBOBOX_DEF_ON_CLICK(int i, void *fn)
{
	dialog[i].fn = fn;	
}

int EDITBOX_MULTILINE_DEF(int x0, int y0, int size_x, int size_y)
{
	dialog[N].hwnd = CreateWindow("EDIT", NULL, WS_VSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY , x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_EDIT_MULTILINE;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	// SendMessage(dialog[N].hwnd, EM_LIMITTEXT, 200, 0);
	return N++;
}

char buf[65536];
int buflen;
void EDITBOX_MULTILINE_APPEND_TEXT( int i, char *newText )
{
	#if 0
	strcat(buf, newText);
	buflen += strlen(newText);
	if (buflen > 100 && 0)
	{
		buflen -= 10;
	 	memmove(buf, &buf[10], buflen);
	 	buf[buflen] = 0;
	}
	
	SetWindowText(dialog[i].hwnd, buf);
    SendMessageA(dialog[i].hwnd, EM_SETSEL, 0, -1); //Select all
	SendMessageA(dialog[i].hwnd, EM_SETSEL, -1, -1);//Unselect and stay at the end pos
	#endif

	// len = GetWindowTextLength(dialog[i].hwnd);

	#if 1
	int len = GetWindowTextLength(dialog[i].hwnd);
	if (len > 100)
	{
		SendMessageA(dialog[i].hwnd, EM_SETSEL, 0, 10); //Select all
		SendMessageA(dialog[i].hwnd, EM_REPLACESEL, 0, (LPARAM)"");
	}
    SendMessageA(dialog[i].hwnd, EM_SETSEL, 0, -1); //Select all
	SendMessageA(dialog[i].hwnd, EM_SETSEL, -1, -1);//Unselect and stay at the end pos
    SendMessageA(dialog[i].hwnd, EM_REPLACESEL, 0, (LPARAM)(newText)); //append text to current pos and scroll down
	#endif
	
	// SendMessage(dialog[i].hwnd, WM_SETREDRAW, 1 ,0);
	// RedrawWindow(dialog[i].hwnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

int LABEL_DEF(int x0, int y0, int size_x, int size_y, char *text)
{
    dialog[N].hwnd = CreateWindow("STATIC","Enter Age:", WS_VISIBLE | WS_CHILD | SS_LEFT, x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_LABEL;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

int LISTBOX_DEF(int x0, int y0, int size_x, int size_y)
{
	dialog[N].hwnd = CreateWindow("LISTBOX", NULL, WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD, x0, y0, size_x, size_y, hWnd, (HMENU)(UINT64)N, GetModuleHandle(NULL), NULL);
	dialog[N].type = TYPE_LISTBOX;
    SendMessage(dialog[N].hwnd, WM_SETFONT, (WPARAM)hf, 0);
	return N++;
}

#define SORT 0
void LISTBOX_ADD(int i, char *item)
{
	SendMessage(dialog[i].hwnd, SORT ? LB_ADDSTRING:LB_INSERTSTRING, 0, (LPARAM) item); 
}

void LISTBOX_DEF_ON_CLICK(int i, void *fn)
{
	dialog[i].fn = fn;	
}