#include <iostream>
#include <exception>

#include "Core.h"

using namespace std;

int main (int argc, char** argv)
{
	Core core;
	
	try
	{
		core.run();
	}
	catch (exception e)
	{
		cerr << "Uncaught exception: " << e.what() << endl;
	}

	return 0;
}