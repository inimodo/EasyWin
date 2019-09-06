#include "src\ews_header.h"

using namespace ews;
console::ews_console o_console;

unsigned char __fastcall ews::main() { 
	o_console.Create(L"Default");
	return 1; 
} 
unsigned char __fastcall ews::update() { 

	return 1; }
void __cdecl ews::close() { 
	o_console.Destroy();

}