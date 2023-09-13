#include <windows.h>
#include <stdio.h>
#include "ui.h"

#define MY_BACKGOUND_COLOR RGB(0,245,0)
#define MY_EDIT_ML_BKCOLOR RGB(0,235,235)

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX class_;

int cnt;
HWND hBtn, hBtn1, hTxt, hTxt1, hTxtML, hCheckBox;
COLORREF backColor;
char attivo;
char checkBoxVal;
HWND hWnd;
HFONT hf;

void app_thread(void *dummy);

void AppendText( HWND hwnd, char *newText )
{
    SendMessageA(hTxtML, EM_SETSEL, 0, -1); //Select all
    SendMessageA(hTxtML, EM_SETSEL, -1, -1);//Unselect and stay at the end pos
    SendMessageA(hTxtML, EM_REPLACESEL, 0, (LPARAM)(newText)); //append text to current pos and scroll down
}

int WINAPI WinMain(HINSTANCE hInstanciaAct, HINSTANCE hInstanciaPrev, LPSTR IpCmdLine, int iCmdShow)
{
    AllocConsole();
    freopen("CONIN$", "r",stdin); 
    freopen("CONOUT$","w",stdout); 
    freopen("CONOUT$","w",stderr); 

    MSG msg;
    
    class_.cbSize = sizeof(WNDCLASSEX);
    class_.cbWndExtra = 0;
    class_.cbClsExtra = 0;
    class_.style = CS_HREDRAW|CS_VREDRAW;
    class_.lpfnWndProc = WndProc;
    class_.hInstance = hInstanciaAct;
    class_.hIcon = LoadImage(NULL, "icoff.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    class_.hIconSm = LoadImage(NULL, "icoff.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    class_.hCursor = LoadCursor(NULL, IDC_ARROW);
    class_.lpszClassName = "MYCLASS";
    class_.lpszMenuName = NULL;
    class_.hbrBackground = CreateSolidBrush(MY_BACKGOUND_COLOR);
    
   
    if(!RegisterClassEx(&class_))
    {
        MessageBox(NULL, "NON", "ERROR", MB_ICONERROR);
        return EXIT_FAILURE;
    }
    
    hWnd = CreateWindowEx(0, "MYCLASS", "Title", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 340, 340, HWND_DESKTOP, NULL, hInstanciaAct, NULL);
    if(hWnd == NULL)
    {
        MessageBox(NULL, "NON2", "ERROR", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    // HBRUSH brush = CreateSolidBrush(RGB(140, 140, 140));
    // SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
    
    ShowWindow(hWnd, iCmdShow);
    
    hf = CreateFont(/*size=*/-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");

    create_widget();

    SendMessage(hWnd,  WM_CHANGEUISTATE, (WPARAM)(0x10001),(LPARAM)(0));

    UpdateWindow(hWnd);

    _beginthread(app_thread , 0, 0);
    
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            break;
        }
                 
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
        
        default:
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        
    }
    return 0;
}
