#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_LISTBOX 100
#define IDC_ELECTIVE 103
#define ID_CLEAR 104
#define ID_GROUP 105
#define IDC_GROUP 106
#define IDC_BUTTON 107
LPSTR ReturnDate(int day, int month, int year);

char szAppName[] = "PopPad1";

HINSTANCE hInst;
HBRUSH hBrush;

HWND hGroup, hListBox, hTake, hButtonGroup, hButtonElective;

char Buf1[80], Buf[80];
HDC hdc1, memdc;
PAINTSTRUCT ps;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, "ГруппаФакультатив", WS_OVERLAPPEDWINDOW, 100, 100, 300, 700, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int i;

	TCHAR buff[256];
	TCHAR buff2[256];
	TCHAR buff3[256];

	switch (uMsg) {
	case WM_CREATE:
		hdc1 = GetDC(hWnd);
		hListBox = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE,
			70, 10, 150, 150, hWnd, (HMENU)ID_LISTBOX, hInst, NULL);

		hGroup = CreateWindowEx(WS_EX_WINDOWEDGE, "button", NULL,
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping
			70, 200, 150, 100,
			hWnd,
			(HMENU)ID_GROUP,
			hInst, NULL);
		hButtonGroup = CreateWindow("BUTTON", "Группа",
			WS_VISIBLE | WS_CHILD | BS_AUTO3STATE | WS_GROUP, // <--— WS_GROUP group the following radio buttons 1st,2nd button
			70, 220, 150, 20, hWnd, (HMENU)IDC_GROUP, hInst, NULL);
		hButtonElective = CreateWindow("BUTTON", "Факультет",
			WS_VISIBLE | WS_CHILD | BS_AUTO3STATE | WS_GROUP, // <--— WS_GROUP group the following radio buttons 1st,2nd button
			70, 240, 150, 20, hWnd, (HMENU)IDC_ELECTIVE, hInst, NULL);
		hTake = CreateWindow("button", "Добавить", WS_CHILD | WS_VISIBLE,
			90, 300, 100, 27, hWnd, (HMENU)IDC_BUTTON, hInst, NULL);
		ReleaseDC(hWnd, hdc1);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			int k = 0;
			WORD nStateGroup, nStateElective;
			nStateGroup = (WORD)SendMessage(hButtonGroup, BM_GETCHECK, 0, 0L);
			nStateElective = (WORD)SendMessage(hButtonElective, BM_GETCHECK, 0, 0L);
			i = SendMessage(hListBox, LB_GETCOUNT, 0, 0L);
			if (nStateGroup > 0) {
				wsprintf(buff, "%s", "Группа");
				k++;
			}
			if (nStateElective > 0)
			{
				wsprintf(buff2, "%s", "факультет");
				k += 2;
			}

			switch (k)
			{
			case 1:
				wsprintf(buff3, "%d %s", i + 1, buff);
				break;
			case 2:
				wsprintf(buff3, "%d %s", i + 1, buff2);
				break;
			case 3:
				wsprintf(buff3, "%d %s %s", i + 1, buff, buff2);
				break;
			}
			if (k == 0) break;
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buff3);
			break;
		}
		default:
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}