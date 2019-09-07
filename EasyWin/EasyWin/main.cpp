#include "src\ews_header.h"

//How to use EWS 2019

using namespace ews;
console::ews_console o_console;

DWORD * dw_pTestImage;

unsigned char __cdecl main() {
	o_console.Create(ews::win::c_WinTitle);
	printf("Created a Console!\n");
#define W 100
#define H 100
	dw_pTestImage = (DWORD*)malloc(sizeof(DWORD)*W*H);
	for (int i = 0, d = 0,x=0; i < H*W; i++, d++)
	{
		if(d % W == 0)
		{
			d = 0;
			x++;
		}
		dw_pTestImage[i] = RGB((int)((float)(i% W / (float)W)* 255.f), (int)((float)(x% H / (float)H)* 255.f),255 );
	}
	return 1; 
} 
unsigned char __cdecl update() {
	printf("Update!\n");

	ews::SetScreenBuffer(dw_pTestImage,W,H);
	return 1; 
}
void __cdecl close() { 
	printf("Closing!\n");
	system("pause");
	o_console.Destroy();
}