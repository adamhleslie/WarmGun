#define WIN32_LEAN_AND_MEAN // Use simplified windows api
#pragma warning(disable:5039) // Disable exception warning in windows api
#include <windows.h>
#pragma warning(default:5039)
#include <exception>

#pragma warning(disable:4100) // Disable warnings related to unused parameters for WinMain
int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try
    {
        // Run program!
        MessageBoxA(nullptr, "WinMain", "Message Box A", MB_ICONINFORMATION);
    }
    catch (std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Uncaught exception", MB_ICONERROR);
    }

    return 0;
}