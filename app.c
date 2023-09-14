#include <windows.h>
#include <stdio.h>
#include "ui.h"

int B1, B2, B3, E1, E2, C1, COMBO1;

void app_thread(void *dummy)
{
    char s[64];
    while(1)
    {
        static int cnt;
        sprintf(s, "%6d", cnt);
        cnt++;
        if (cnt == 20)
            cnt = 0;
        ENABLE_WIDGET(B1, cnt > 10);
        ENABLE_WIDGET(B2, cnt > 10);
        RO_WIDGET(E1, cnt > 10);
        printf("%d", cnt > 10);
        Sleep(100);
        printf("."); fflush(stdout);
        continue;
        
        #if 0
        char tmp[64];
        int editlength = GetWindowTextLength(hTxt1);
        GetWindowText(hTxt1, tmp, editlength+1);
        printf("[%s]", tmp);
        
        if (checkBoxVal)
        {
                AppendText(hTxtML, "\r\n");
                AppendText(hTxtML, s);
                UpdateWindow(hTxtML);
        }
        SetWindowText( hTxt, s);
        if (cnt>10)
        {
                attivo=1;
                backColor=RGB(255,255,0);
                UpdateWindow(hTxt);
                EnableWindow(hBtn1, FALSE);
        }
        if (cnt>100)
                EnableWindow(hTxt, FALSE);
        #endif
    }
}

void B_pressed(int i)
{
	printf("pressed %d\n", i);
}

void Text_changed(int i)
{
	printf("Text changed %d\n", i);
}

void CheckBox_change(int i)
{
	printf("Checkbox change %d\n", i);
	EDIT_SET_TEXT(E1, "");
	EDIT_SET_TEXT(E2, "");
}

void create_widget(void)
{
    B1 = BUTTON_DEF  (10,  8,   175, 22, "B1");
    B2 = BUTTON_DEF  (10,  38,  175, 22, "B2");
    B3 = BUTTON_DEF  (10,  68,  175, 22, "B3");
    E1 = EDIT_DEF    (10,  98,  175, 22, "");
    E2 = EDIT_DEF    (10, 128,  175, 22, "");
    C1 = CHECKBOX_DEF(10, 158,  175, 22, "checkbox");

    COMBO1 = COMBOBOX_DEF(10, 188,  175, 22, "combobox");
    COMBOBOX_ADD(COMBO1, "item1");
    COMBOBOX_ADD(COMBO1, "item2");
    COMBOBOX_ADD(COMBO1, "item3");
    COMBOBOX_ADD(COMBO1, "item4");

    BUTTON_DEF_ON_CLICK(B1, B_pressed);
    BUTTON_DEF_ON_CLICK(B2, B_pressed);
    BUTTON_DEF_ON_CLICK(B3, B_pressed);

    EDITBOX_DEF_ON_CHANGE(E1, Text_changed);
    EDITBOX_DEF_ON_CHANGE(E2, Text_changed);

    CHECKBOX_DEF_ON_CLICK(C1, CheckBox_change);

}
