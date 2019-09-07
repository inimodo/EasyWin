#pragma once

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

#ifndef UNICODE
#define UNICODE
#endif 

#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<iostream>

#define TOCLIENTWIDTH(x) (ews::win::i_Width-16)
#define TOCLIENTHEIGHT(x) (ews::win::i_Height-39)

//EasyWin Socket for C++ 
// Markus Kotar @ UCPSystems.com 2019

extern HANDLE __fastcall CreateExec(HINSTANCE h_Instance);
extern long __stdcall WindowProc(HWND hd_Handle, UINT msg_Message, WPARAM wParam, LPARAM lParam);
extern int __stdcall wWinMain(HINSTANCE h_Instance, HINSTANCE, PWSTR c_pCmdLine, int i_CmdShow);

/* Premade Functions 

unsigned char __fastcall ews::win::main() { return 1; } //Gets Calledd once before Window Creation
unsigned char __fastcall ews::win::update() { return 1; } // Gets Called every "WindowProc" Call
void __cdecl ews::win::close() { } // Gets Called before window closing

*/

extern unsigned char __fastcall main();
extern unsigned char __fastcall update();
void __cdecl close();

namespace ews {


	extern void  SetScreenBuffer(DWORD * dw_ColorStream);

	namespace win {

		const static DWORD dw_ExStyle = 0;
		const static wchar_t * c_WinClassName = L"WINCLASSEWS";
		const static wchar_t * c_WinTitle = L"Default Title";
		const static DWORD  dw_Style = (WS_OVERLAPPED  | WS_SYSMENU | WS_MINIMIZEBOX );
		const static int i_XPos = CW_USEDEFAULT;
		const static int i_YPos = CW_USEDEFAULT;
		const static int i_Width = 1600;
		const static int i_Height = 900;
		const static HWND hd_WndParent = NULL;
		const static HMENU h_Menu = NULL;
		static HINSTANCE h_Instance = NULL;
		const static LPVOID lp_Param = NULL;
		
		static HWND hd_WindowHandle;
		static MSG msg_WindowMessage;
		static HDC hdc_WindowHdc;


		static  WNDCLASS w_WndClass = { };
		

	}
	namespace console {
		class ews_console {
		public:
			BOOL Create(const wchar_t* c_ConsoleTitle);
			BOOL Create();

			void Clear();
			BOOL __stdcall Destroy();
			BOOL __stdcall Rename(const wchar_t* c_ConsoleTitle);

			void SetColor(const int i_HexColor);
		private:
			BOOL __stdcall AllocC();
		};
	}
}