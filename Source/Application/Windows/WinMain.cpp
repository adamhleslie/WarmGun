#define WIN32_LEAN_AND_MEAN // Use simplified windows api

#pragma warning(disable:5039) // Disable exception warning in windows api
#include <windows.h>
#pragma warning(default:5039)

#include <exception>
#include <cstdio>
#include "Core.h"

#pragma warning(disable:4100) // Disable warnings related to unused parameters for WinMain
int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!AllocConsole())
	{
		return 1;
	}

	// Open streams: std::cout, std::cerr, std::cin
	FILE* filePtr;
	freopen_s(&filePtr, "CONOUT$", "w", stdout);
	freopen_s(&filePtr, "CONOUT$", "w", stderr);
	freopen_s(&filePtr, "CONIN$", "r", stdin);

	try
    {
        // Run the application!
        Core core;
        core.Run();
    }
    catch (std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Uncaught exception", MB_ICONERROR);
    }

    return 0;
}
