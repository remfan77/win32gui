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
