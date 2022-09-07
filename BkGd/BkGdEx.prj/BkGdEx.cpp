// BkGdEx.cpp : Defines the entry point for the application.


#include "framework.h"
#include "BkGdEx.h"
#include "IniFile.h"
#include "WallPaper.h"


#define MAX_LOADSTRING 100


// Global Variables:

static HINSTANCE hInst;                                    // current instance
static String    path;
static uint      timerID;


// Function declarations

static ATOM             MyRegisterClass(String& wdwClass);
static BOOL             InitInstance(int nCmdShow);
static void             getTitle(String& title);
static void             initialize();
static void             next();
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
static VOID    CALLBACK timerProc(HWND hWnd, uint nmsg, uint nIDEvent, DWORD dwTime);


// Starting Point

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow) {
HACCEL hAccelTable;
MSG    msg;

  hInst = hInstance;                                  // Store instance handle in our global variable

  iniFile.getAppDataPath(_T("BkGd"));
  if (!iniFile.readInt(Section, EnabledKey, 0)) return 0;

  if (!InitInstance(nCmdShow)) return FALSE;          // Perform application initialization:

  hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_BKGDEX));

  initialize();

  if (!timerID) return 1;

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0)) {

    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                                                          {TranslateMessage(&msg); DispatchMessage(&msg);}
    }

  return (int) msg.wParam;
  }


//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.

BOOL InitInstance(int nCmdShow) {
String title;
String wdwClass;

  MyRegisterClass(wdwClass);

  getTitle(title);

  HWND hWnd = CreateWindowW(wdwClass, title, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_MESSAGE, nullptr, hInst, nullptr);
  if (!hWnd) return FALSE;

  ShowWindow(hWnd, nCmdShow);   UpdateWindow(hWnd);   return TRUE;
  }


//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.

ATOM MyRegisterClass(String& wdwClass) {
WNDCLASSEX wcex;
Tchar       szWindowClass[MAX_LOADSTRING];                    // the main window class name

  LoadStringW(hInst, IDC_BKGDEX, szWindowClass, MAX_LOADSTRING);   wdwClass = szWindowClass;

  wcex.cbSize         = sizeof(WNDCLASSEX);
  wcex.style          = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc    = WndProc;
  wcex.cbClsExtra     = 0;
  wcex.cbWndExtra     = 0;
  wcex.hInstance      = hInst;
  wcex.hIcon          = LoadIcon(hInst, MAKEINTRESOURCE(IDI_BKGDEX));
  wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BKGDEX);
  wcex.lpszClassName  = wdwClass;                           //szWindowClass;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassEx(&wcex);
  }


void getTitle(String& title) {
Tchar  heading[MAX_LOADSTRING];
Tchar  buf[UNLEN+1];
DWORD  len = noElements(buf);

  LoadStringW(hInst, IDS_APP_TITLE, heading, MAX_LOADSTRING);

  if (GetUserName(buf, &len)) {title = buf; title += _T(' ');}   title += heading;
  }


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_COMMAND : { int wmId = LOWORD(wParam);
                        // Parse the menu selections:
                        switch (wmId) {
                          case IDM_ABOUT      : DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX),
                                                                                            hWnd, About);
                                                break;

                          case IDM_Initialize : KillTimer(NULL, timerID);   initialize(); break;

                          case IDM_Next       : KillTimer(NULL, timerID);   next(); break;

                          case IDM_Mode       : wallPaper.getMode(); break;

                          case IDM_EXIT       : DestroyWindow(hWnd); break;

                          default             : return DefWindowProc(hWnd, message, wParam, lParam);
                          }
                        }
                      break;

    case WM_PAINT   : { PAINTSTRUCT ps;
                        HDC         hdc = BeginPaint(hWnd, &ps);
                        // TODO: Add any drawing code that uses hdc here...
                        EndPaint(hWnd, &ps);
                        }
                      break;

    case WM_DESTROY : PostQuitMessage(0);   KillTimer(NULL, timerID);   break;

    default         : return DefWindowProc(hWnd, message, wParam, lParam);
    }

  return 0;
  }


void initialize() {

  wallPaper.initialize();

  if (!iniFile.readString(Section, WallPaperKey, path) || !wallPaper.findAll(path)) return;

  next();
  }


void next() {
int interval;

  wallPaper.set();

  interval = iniFile.readInt(Section, IntervalKey, 1);

  timerID = SetTimer(0, 0, interval * 60000, &timerProc);
  }



// Message handler for about box.

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

  switch (message) {
    case WM_INITDIALOG: return (INT_PTR)TRUE;

    case WM_COMMAND   : if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
                                                {EndDialog(hDlg, LOWORD(wParam));   return (INT_PTR)TRUE;}
                        break;
    }

  return (INT_PTR)FALSE;
  }



VOID CALLBACK timerProc(HWND hWnd, uint nmsg, uint nIDEvent, DWORD dwTime) {wallPaper.set();}


