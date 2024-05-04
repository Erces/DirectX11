#include <iostream>
#include "ErceWin.h"
#include <sstream>
#include "Window.h"
#include "App.h"

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
try
{
	return App{}.Start();
}
catch (const ErceException& e) 
{
	MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
}
catch (const std::exception& e)
{
	MessageBox(nullptr, e.what(), "Standart Exception", MB_OK | MB_ICONEXCLAMATION);
}
catch (...)
{
	MessageBox(nullptr, "No Details", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
}

return -1;

}

