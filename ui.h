// #pragma once

#define N_MAX 100

#define TYPE_BUTTON   0
#define TYPE_EDITBOX  1
#define TYPE_CHECKBOX 2

struct DIALOG
{
	int x0;
	int y0;
	int size_x;
	int size_y;
	char type;
	HWND hwnd;
	int id;
	char *text;
	void (*fn)(int i);
};

extern int N;
extern struct DIALOG dialog[N_MAX];

extern int B1, B2, B3, E1, E2, C1;

int  BUTTON_DEF(int x0, int y0, int size_x, int size_y, char *text);
void BUTTON_DEF_ON_CLICK(int i, void *fn);
int  EDIT_DEF(int x0, int y0, int size_x, int size_y, char *text);
void EDITBOX_DEF_ON_CHANGE(int i, void *fn);
void EDIT_SET_TEXT(int i, char *text);
int  CHECKBOX_DEF(int x0, int y0, int size_x, int size_y, char *text);
void CHECKBOX_DEF_ON_CLICK(int i, void *fn);
void ENABLE_WIDGET(int i, int state);
void RO_WIDGET(int i, int state);
