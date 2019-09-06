#include"ews_header.h"

HANDLE __fastcall CreateExec(HINSTANCE h_Instance);
long __stdcall WindowProc(HWND hd_Handle, UINT msg_Message, WPARAM wParam, LPARAM lParam);

int __stdcall wWinMain(HINSTANCE h_Instance, HINSTANCE, PWSTR c_pCmdLine, int i_CmdShow)
{
	if (ews::main() == NULL) 
	{
		return NULL;
	}

	if (CreateExec(h_Instance) == NULL)
	{
		return NULL;
	}
	ShowWindow(ews::win::hd_WindowHandle, i_CmdShow);	
	UpdateWindow(ews::win::hd_WindowHandle);

	ews::win::hdc_WindowHdc = GetDC(ews::win::hd_WindowHandle);
	while (GetMessage(&ews::win::msg_WindowMessage, NULL, 0, 0)>0)
	{
		if (ews::update() == NULL)
		{
			return NULL;
		}
		TranslateMessage(&ews::win::msg_WindowMessage);
		DispatchMessage(&ews::win::msg_WindowMessage);
	}

	ews::close();
	ReleaseDC(NULL,ews::win::hdc_WindowHdc);
	return NULL;
}
HANDLE __fastcall CreateExec(HINSTANCE h_Instance) {
	ews::win::w_WndClass.hbrBackground = (HBRUSH)(2);
	ews::win::w_WndClass = {0};
	ews::win::w_WndClass.lpfnWndProc = (WNDPROC)WindowProc;
	ews::win::w_WndClass.hInstance = h_Instance;
	ews::win::w_WndClass.lpszClassName = ews::win::c_WinClassName;

	RegisterClass(&ews::win::w_WndClass);

	ews::win::h_Instance = h_Instance;
	ews::win::hd_WindowHandle = CreateWindowEx(
		ews::win::dw_ExStyle,
		ews::win::c_WinClassName,
		ews::win::c_WinTitle,
		ews::win::dw_Style,
		ews::win::i_XPos,
		ews::win::i_YPos,
		ews::win::i_Width,
		ews::win::i_Height,
		ews::win::hd_WndParent,
		ews::win::h_Menu,
		h_Instance,
		ews::win::lp_Param
	);
	return ews::win::hd_WindowHandle;
}
long __stdcall WindowProc(HWND hd_Handle, UINT msg_Message, WPARAM wParam, LPARAM lParam)
{
	
	if (msg_Message == WM_CLOSE) {
		DestroyWindow(hd_Handle);
		return 0;

	}
	if (msg_Message == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}
	
	DefWindowProcW(hd_Handle, msg_Message, wParam, lParam);

}
void  ews::SetScreenBuffer(DWORD * dw_ColorStream) {
	HBITMAP bmp_Bitmap = CreateBitmap(TOCLIENTWIDTH(ews::win::i_Width), TOCLIENTHEIGHT(ews::win::i_Height),1,8*4,(const void *) dw_ColorStream);
	HDC hdc_TempHdc = CreateCompatibleDC(ews::win::hdc_WindowHdc);
	SelectObject(hdc_TempHdc, bmp_Bitmap);
	BitBlt(ews::win::hdc_WindowHdc,0,0, TOCLIENTWIDTH(ews::win::i_Width), TOCLIENTHEIGHT(ews::win::i_Height), hdc_TempHdc,0,0,SRCCOPY);
	DeleteObject(bmp_Bitmap);
	DeleteDC(hdc_TempHdc);
}