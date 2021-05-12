// Characters.cpp : Определяет точку входа для приложения.
//


#include "framework.h"
#include "Main.h"
#include "DisplayManager.h"


#define MAX_LOADSTRING 100



// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
Display* display;
std::string text;
DisplayManager* dm;
HWND hInText, hExe, hHead, hСaption;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHARACTERS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHARACTERS));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = 0;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = 0;

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   return TRUE;
}


std::string narrow(const std::wstring& str)
{
    std::ostringstream stm;
    const std::ctype<char>& ctfacet = std::use_facet<std::ctype<char> >(stm.getloc());
    for (size_t i = 0; i < str.size(); ++i)
        stm << ctfacet.narrow(str[i], 0);
    return stm.str();
}

void create_units(HWND hWnd) {


    hСaption = CreateWindow(
        L"Static", L"Valid characters: \n'ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n.!?'", WS_CHILD | WS_VISIBLE,
        50, 10, 250, 70,
        hWnd, NULL, NULL, NULL);

    hHead = CreateWindow(
        L"Static", L"Text in english:", WS_CHILD | WS_VISIBLE,
        350, 10, 100, 20,
        hWnd, NULL, NULL, NULL);
    hInText = CreateWindow(
        L"edit", L"Flyweights! One man wanted to make a special gift for his mother on the Mothers day. He run out of ideas but then found a pet shop where was birds that could sing talk and dance. The price was thousand dollars but he bought two of them and send to his mother as a surprise. Next day he called to his mother and asked how she liked the present. Oh they was delicious thank you she answered. He got upset and said Mom this were expensive birds they cost me  thousand dollars and they could sing and talk and dance. And his mother answered Well they shouldve said something.",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE,
        350, 30, 500, 150,
        hWnd, NULL, NULL, NULL);
    hExe = CreateWindow(
        L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        900, 80, 100, 50,
        hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_1), NULL, NULL);

    RECT rect;
    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;
    display = new Display(width, height);
    dm = new DisplayManager(display, 40, 200);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
       
    switch (message)
    {
    case WM_CREATE: {
        create_units(hWnd);
    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDC_BUTTON_1:
                wchar_t buff[1024];
                GetWindowText(hInText, buff, 1023);
                text = narrow(buff);
                InvalidateRect(hWnd, nullptr, TRUE);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

            RECT rect;
            GetWindowRect(hWnd, &rect);
            LONG width = rect.right - rect.left;
            LONG height = rect.bottom - rect.top;
            display = new Display(height, width);
            dm->changeDisplay(display);

            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hWnd, &ps);  

            if (!dm->renderChs(hdc, text)) {  // Main Program
                cptrwc error = L"Invalide characters!";
                SetWindowText(hInText, error);
            };
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
