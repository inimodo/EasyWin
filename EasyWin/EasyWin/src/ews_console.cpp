#include "ews_header.h"


BOOL ews::console::ews_console::Create() 
{
	return AllocC();
}
BOOL ews::console::ews_console::Create(const wchar_t* c_ConsoleTitle)
{
	if (AllocC() == NULL) {
		return NULL;
	}
	Rename(c_ConsoleTitle);
}
BOOL __stdcall ews::console::ews_console::AllocC()
{
	if (AllocConsole() == NULL) {
		return NULL;
	}
	freopen("CON", "w", stdout);
	return 1;
}
BOOL __stdcall ews::console::ews_console::Rename(const wchar_t* c_ConsoleTitle)
{
	return SetConsoleTitleW(c_ConsoleTitle);

}
BOOL __stdcall ews::console::ews_console::Destroy() 
{
	return FreeConsole();
}