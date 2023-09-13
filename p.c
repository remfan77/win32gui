#include <windows.h>
#include <stdio.h>

#define ID_BTN      0
#define ID_BTN_1    1
#define ID_TXT      2
#define ID_TXT1     3
#define ID_TXT_ML   4
#define ID_CHECKBOX 5 

#define MY_BACKGOUND_COLOR RGB(245,245,245)
#define MY_EDIT_ML_BKCOLOR RGB(235,235,235)

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX class_;

int cnt;
HWND hBtn, hBtn1, hTxt, hTxt1, hTxtML, hCheckBox;
COLORREF backColor;
char attivo;
char checkBoxVal;

void fn(void *dummy)
{
	char s[64];
	while(1)
	{
		sprintf(s, "%6d", cnt++);
		Sleep(100);
		printf("."); fflush(stdout);
		
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
	}
}

int WINAPI WinMain(HINSTANCE hInstanciaAct, HINSTANCE hInstanciaPrev, LPSTR IpCmdLine, int iCmdShow){
    
    AllocConsole();
    freopen("CONIN$", "r",stdin); 
    freopen("CONOUT$","w",stdout); 
    freopen("CONOUT$","w",stderr); 

    HWND hWnd;
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
    
    hBtn      = CreateWindow("BUTTON", "RESET",     WS_VISIBLE | WS_CHILD | BS_PUSHLIKE ,  10, 8,  175, 22, hWnd, (HMENU)ID_BTN,   GetModuleHandle(NULL), NULL);
    hBtn1     = CreateWindow("BUTTON", "B1",        WS_VISIBLE | WS_CHILD | BS_PUSHLIKE , 200, 8,   75, 52, hWnd, (HMENU)ID_BTN_1, GetModuleHandle(NULL), NULL);
    hTxt      = CreateWindow("EDIT",   0,           WS_VISIBLE | WS_CHILD | WS_BORDER ,    10, 38, 175, 22, hWnd, (HMENU)ID_TXT,   GetModuleHandle(NULL), NULL);
    hTxt1     = CreateWindow("EDIT",   0,           WS_VISIBLE | WS_CHILD | WS_BORDER ,    10, 68, 175, 22, hWnd, (HMENU)ID_TXT1,  GetModuleHandle(NULL), NULL);
    hTxtML    = CreateWindow("EDIT",   0,           WS_VSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,  10, 180, 290, 90, hWnd, (HMENU)ID_TXT_ML,   GetModuleHandle(NULL), NULL);
    hCheckBox = CreateWindow("BUTTON", "RUNNING",   WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,195,100, 100, 14, hWnd,(HMENU)ID_CHECKBOX,NULL,NULL);
    // EnableWindow(hTxtML, FALSE);
    
    HFONT hf = CreateFont(/*size=*/-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
    SendMessage(hTxt,       WM_SETFONT, (WPARAM)hf, 0);
    SendMessage(hTxt1,      WM_SETFONT, (WPARAM)hf, 0);
    SendMessage(hTxtML,     WM_SETFONT, (WPARAM)hf, 0);
    SendMessage(hBtn,       WM_SETFONT, (WPARAM)hf, 0);
    SendMessage(hBtn1,      WM_SETFONT, (WPARAM)hf, 0);
    SendMessage(hCheckBox,  WM_SETFONT, (WPARAM)hf, 0);
    
    SendMessage(hWnd,  WM_CHANGEUISTATE, (WPARAM)(0x10001),(LPARAM)(0));
    
    UpdateWindow(hWnd);

    _beginthread(fn , 0, 0);
    
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

char buf[1024*1024];

void AppendText( HWND hwnd, char *newText )
{
    SendMessageA(hTxtML, EM_SETSEL, 0, -1); //Select all
    SendMessageA(hTxtML, EM_SETSEL, -1, -1);//Unselect and stay at the end pos
    SendMessageA(hTxtML, EM_REPLACESEL, 0, (LPARAM)(newText)); //append text to current pos and scroll down
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CREATE:{
            // hBtn = CreateWindow("BUTTON", "RESET",     WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 82.5, 48, 175, 22.5, hWnd, (HMENU)ID_BTNHI, GetModuleHandle(NULL), NULL);
            // hTxt = CreateWindow("EDIT",   "0",         WS_VISIBLE | WS_CHILD | WS_BORDER,        82.5, 98, 175, 22.5,   hWnd, (HMENU)ID_TXT, GetModuleHandle(NULL), NULL);
            break;
        }
        
         
        /* Colore text box EDITABILE */
        case WM_CTLCOLOREDIT:
        {
          HDC hdc = (HDC)wParam;
          if (attivo && (HANDLE)lParam==hTxt)
          {
		// printf("ECCOLO1\n");
		SetTextColor(hdc, RGB(0,100,255));  // yourColor is a WORD and it's format is 0x00BBGGRR
		SetBkColor(hdc, RGB(255,255,0));  // yourColor is a WORD and it's format is 0x00BBGGRR
		return CreateSolidBrush(RGB(255,255,0));
	  }
          return (LRESULT) GetStockObject(DC_BRUSH); // return a DC brush.
        }
        
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_BTN:
                {
                    printf("checkbox\n");
                    cnt = 0;
                    break;
                }
                case ID_CHECKBOX:
			printf("checkbox\n");
			checkBoxVal = !checkBoxVal;
			break;
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

        /* Etichetta checkbox       */
        /* Edit Multiline READ ONLY */
        case WM_CTLCOLORSTATIC:
        {
          if ((HANDLE)lParam==hTxtML)
          {
                HDC hdc = (HDC)wParam;
                printf("ECCOLO\n");
                SetBkColor(hdc, MY_EDIT_ML_BKCOLOR);
                return (LRESULT) CreateSolidBrush(MY_EDIT_ML_BKCOLOR); //GetStockObject(DC_BRUSH); // return a DC brush.
          }

		return CreateSolidBrush(MY_BACKGOUND_COLOR); // GetSysColorBrush(COLOR_WINDOW);/* (LRESULT)hBrushColor;*/
	}
        
        default:
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        
    }
    return 0;
}
