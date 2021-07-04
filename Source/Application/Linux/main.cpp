#include <iostream>
#include <exception>

int main (int argc, char** argv)
{
    try
    {
        // Run program!
        std::cout << "Hello World!" << std::endl;
    }
    catch (std::exception e)
    {
        std::cerr << "Uncaught exception: " << e.what() << std::endl;
    }

    return 0;
}