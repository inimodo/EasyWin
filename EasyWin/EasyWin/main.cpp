#include "src\ews_header.h"

//How to use EWS 2019

using namespace ews;
console::ews_console o_console;

DWORD * dw_pTestImage;

unsigned char __fastcall ews::main() { 
	o_console.Create(ews::win::c_WinTitle);
	printf("Created a Console!\n");

	dw_pTestImage = (DWORD*)malloc(sizeof(DWORD)*TOCLIENTWIDTH(ews::win::i_Width)*TOCLIENTHEIGHT(ews::win::i_Height));
	for (int i = 0, d = 0,x=0; i < TOCLIENTWIDTH(ews::win::i_Width)*TOCLIENTHEIGHT(ews::win::i_Height); i++, d++)
	{
		if(d % TOCLIENTWIDTH(ews::win::i_Width) == 0)
		{
			d = 0;
			x++;
		}
		dw_pTestImage[i] = RGB((int)((float)(i% TOCLIENTWIDTH(ews::win::i_Width) / (float)TOCLIENTWIDTH(ews::win::i_Width))* 255.f), (int)((float)(x% TOCLIENTHEIGHT(ews::win::i_Height) / (float)TOCLIENTHEIGHT(ews::win::i_Height))* 255.f),255 );
	}
	return 1; 
} 
unsigned char __fastcall ews::update() { 
	printf("Update!\n");

	ews::SetScreenBuffer(dw_pTestImage);
	return 1; 
}
void __cdecl ews::close() { 
	printf("Closing!\n");
	system("pause");
	o_console.Destroy();
}