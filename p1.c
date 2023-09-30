#include <windows.h>
#include <stdio.h>
#include "ui.h"

#define SIMPLE 1

#define MY_BACKGOUND_COLOR RGB(0,245,0)
#define MY_EDIT_ML_BKCOLOR RGB(0,235,235)

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX class_;

COLORREF backColor;
char attivo;
HWND hWnd;
HFONT hf;
int font_h;

void app_thread(void *dummy);

// int /*WINAPI*/ myWinMain(int size_x, int size_y) // (HINSTANCE __hInstanciaAct, HINSTANCE __hInstanciaPrev, LPSTR __IpCmdLine, int __iCmdShow)
int create_main_win(int size_x, int size_y)
{
    AllocConsole();
    freopen("CONIN$", "r",stdin); 
    freopen("CONOUT$","w",stdout); 
    freopen("CONOUT$","w",stderr); 

    // __hInstanciaAct = 0;
    // __iCmdShow = 1;
    
    class_.cbSize = sizeof(WNDCLASSEX);
    class_.cbWndExtra = 0;
    class_.cbClsExtra = 0;
    class_.style = CS_HREDRAW|CS_VREDRAW;
    class_.lpfnWndProc = WndProc;
    class_.hInstance = 0; //__hInstanciaAct;
    class_.hIcon = LoadImage(NULL, "icoff.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    class_.hIconSm = LoadImage(NULL, "icoff.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    class_.hCursor = LoadCursor(NULL, IDC_ARROW);
    class_.lpszClassName = "MYCLASS";
    class_.lpszMenuName = NULL;
    class_.hbrBackground = SIMPLE ?
        (HBRUSH)(COLOR_WINDOW) :
        CreateSolidBrush(MY_BACKGOUND_COLOR);    
   
    if(!RegisterClassEx(&class_))
    {
        MessageBox(NULL, "NON", "ERROR", MB_ICONERROR);
        return EXIT_FAILURE;
    }
    
    hWnd = CreateWindowEx(0,
                          "MYCLASS",
                          "Title",
                          WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
                          size_x, size_y, HWND_DESKTOP, NULL, 0/*__hInstanciaAct*/, NULL);
    if(hWnd == NULL)
    {
        MessageBox(NULL, "NON2", "ERROR", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    // HBRUSH brush = CreateSolidBrush(RGB(140, 140, 140));
    // SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
    
    ShowWindow(hWnd, 1/*__iCmdShow*/);
    
    hf = CreateFont(/*size=*/15, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
    
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hf, 0);
    
    // TEXTMETRIC tm;
    // GetTextMetrics(GetDC(hWnd), &tm);
    // font_h =  (tm.tmHeight + tm.tmExternalLeading) + 14;
    // GetDeviceCaps(GetDC(hWnd), LOGPIXELSY) / 72;

    // (10*15+9)/10; // +2; // FM.tmHeight+10;
    // DWORD nExStyles = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
    // if(nExStyles & WS_EX_CLIENTEDGE)
	//    font_h += GetSystemMetrics(SM_CYEDGE) * 2;
    // if(nExStyles & WS_EX_STATICEDGE)
	//    font_h += GetSystemMetrics(SM_CYBORDER) * 2;
}

void main_loop(void)
{
    MSG msg;
    // create_widget();

    SendMessage(hWnd,  WM_CHANGEUISTATE, (WPARAM)(0x10001),(LPARAM)(0));

    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            break;
        }
                 
        case WM_COMMAND:
        {
            // switch(LOWORD(wParam))
            // {
                int j;
                // static int cnt;
                // printf("%5d WM_COMMAND %d %d\n", cnt++, LOWORD(wParam), HIWORD(wParam));
                for (j = 0; j < N; j++)
                {
                    if (LOWORD(wParam) == j)
                    {
                        switch (dialog[j].type)
                        {
                            case TYPE_CHECKBOX:
                            case TYPE_BUTTON:
                                if (dialog[j].fn)
                                {
                                    dialog[j].fn(j);
                                }
                                break;

                            case TYPE_EDITBOX:
                                if (HIWORD(wParam) == EN_CHANGE)
                                {
                                    if (dialog[j].fn)
                                    {
                                        dialog[j].fn(j);
                                    }
                                }
                                break;
                            
                            case TYPE_LISTBOX:
                                if (HIWORD(wParam) == LBN_SELCHANGE)
                                {
                                    if (dialog[j].fn)
                                    {
                                        dialog[j].fn(j);
                                    }
                                }
                                break;
                            case TYPE_COMBOBOX:
                                if (HIWORD(wParam) == CBN_SELCHANGE)
                                {
                                    if (dialog[j].fn)
                                    {
                                        dialog[j].fn(j);
                                    }
                                }
                                break;
                        }
                }
            }
            break;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        #if SIMPLE == 0
        /* Colore text box EDITABILE */
        case WM_CTLCOLOREDIT:
        {
          HDC hdc = (HDC)wParam;
          if (/*attivo &&*/ (HANDLE)lParam==dialog[E1].hwnd)
          {
                // printf("ECCOLO1\n");
                SetTextColor(hdc, RGB(0,100,255));  // yourColor is a WORD and it's format is 0x00BBGGRR
                SetBkColor(hdc, RGB(255,255,0));  // yourColor is a WORD and it's format is 0x00BBGGRR
                return (LRESULT)CreateSolidBrush(RGB(255,255,0));
          }
          return (LRESULT) GetStockObject(DC_BRUSH); // return a DC brush.
        }

        /* Bordo bottoni */
        case WM_CTLCOLORBTN:
        {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, MY_BACKGOUND_COLOR);
            return (LRESULT)CreateSolidBrush(MY_BACKGOUND_COLOR); // GetSysColorBrush(COLOR_WINDOW);/* (LRESULT)hBrushColor;*/
        }

        /* Etichetta checkbox       */
        /* Edit Multiline READ ONLY */
        case WM_CTLCOLORSTATIC:
        {
          // if ((HANDLE)lParam==dialog[E1].hwnd)
          // {
                HDC hdc = (HDC)wParam;
                printf("ECCOLO\n");
                SetBkColor(hdc, MY_EDIT_ML_BKCOLOR);
          //       return (LRESULT) CreateSolidBrush(MY_EDIT_ML_BKCOLOR); //GetStockObject(DC_BRUSH); // return a DC brush.
          // }
                return (LRESULT)CreateSolidBrush(MY_EDIT_ML_BKCOLOR); // GetSysColorBrush(COLOR_WINDOW);/* (LRESULT)hBrushColor;*/
        }
        #endif
        
        default:
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        
    }
    return 0;
}
