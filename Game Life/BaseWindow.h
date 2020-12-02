#pragma once

#include "pch.h"

template<class EVENT_PROC_CLASS>
class Window
{
public:
	static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		EVENT_PROC_CLASS* pHandle;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT)lParam;
			pHandle = reinterpret_cast<EVENT_PROC_CLASS>(pCreate);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pHandle);
		}
		else
		{
			pHandle = GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		if (pHandle != NULL)
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	static BOOL InitializeWindowClass()
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = Window::WndProc;
		wcex.hInstance = hInstance;
		wcex.hCursor = LoadCursor(NULL, id_cursor);
		wcex.lpszClassName = className();
		wcex.hIcon = LoadIcon(NULL, id_icon);
		wcex.hIconSm = LoadIcon(NULL, id_icon);
		wcex.hbrBackground = backGround;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.lpszMenuName = szMenuName.c_str();
		wcex.style = CS_HREDRAW | CS_VREDRAW;

	}
protected:
	HINSTANCE hInstance;
	WORD id_cursor;
	WORD id_icon;
	HBRUSH backGround;
	wstring szMenuName;
	virtual const LPCTSTR className()
	{
		return "Window";
	}
};