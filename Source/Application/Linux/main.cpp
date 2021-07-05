#include <iostream>
#include <exception>
#include "Core.h"

int main (int argc, char** argv)
{
    try
    {
        // Run the application!
        Core core;
        core.Run();
    }
    catch (std::exception e)
    {
        std::cerr << "Uncaught exception: " << e.what() << std::endl;
    }

    return 0;
}