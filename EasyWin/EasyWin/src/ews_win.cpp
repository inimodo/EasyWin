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
	ews::win::hdc_WindowHdc = GetDC(ews::win::hd_WindowHandle);

	while (GetMessage(&ews::win::msg_WindowMessage, NULL, 0, 0))
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
	ews::win::w_WndClass.lpfnWndProc = WindowProc;
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
		ews::win::h_Instance,
		ews::win::lp_Param
	);
	return ews::win::hd_WindowHandle;
}
long __stdcall WindowProc(HWND hd_Handle, UINT msg_Message, WPARAM wParam, LPARAM lParam)
{
	switch (msg_Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hd_Handle, &ps);



		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hd_Handle, &ps);
	}
	return 0;

	}
	return DefWindowProc(hd_Handle, msg_Message, wParam, lParam);
}
void __fastcall ews::SetScreenBuffer(DWORD * dw_ColorStream) {
	HBITMAP bmp_Bitmap = CreateBitmap(ews::win::i_Width, ews::win::i_Height,1,8*4,(void *) dw_ColorStream);
	HDC hdc_TempHdc = CreateCompatibleDC(ews::win::hdc_WindowHdc);
	SelectObject(hdc_TempHdc, bmp_Bitmap);
	BitBlt(hdc_TempHdc,0,0, ews::win::i_Width, ews::win::i_Height, ews::win::hdc_WindowHdc,0,0,SRCCOPY);
	DeleteObject(bmp_Bitmap);
	DeleteDC(hdc_TempHdc);
}