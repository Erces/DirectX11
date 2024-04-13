#include <iostream>
#include "ErceWin.h"
#include <sstream>
#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	//Adding Behaviour
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "IM BACK");
		}
		break;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
	}
	break;

		
	case WM_CHAR:
		static std::string title;
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdWindow
)
{
	Window wnd(800, 300, "Test");

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam;
	}
	return 0;
}