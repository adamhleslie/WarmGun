#include <exception>
#include <windows.h>

#include "Core.h"

using namespace std;

int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Core core;

	try
	{
		core.run();
	}
	catch (exception e)
	{
		MessageBoxA(nullptr, e.what(), "Uncaught exception", MB_ICONERROR);
	}

	return 0;
}