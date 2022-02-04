#include "Utilities.h"

#include <iostream>
#include <fstream>

bool Utilities::ReadFile(const std::filesystem::path& path, std::string& contents)
{
	// Check for file
	std::error_code filesystemError;
	if (!std::filesystem::is_regular_file(path, filesystemError))
	{
		if (filesystemError)
		{
			std::cout << "[Utilities.ReadFile] Error - Path, \"" << path.string() << "\", does not point to a regular file: " << filesystemError.message() << std::endl;
		}

		return false;
	}

	// Open file
	std::ifstream shaderFile{path};
	if (shaderFile.fail())
	{
		std::cout << "[Utilities.ReadFile] Error - Opening file, \"" << path.string() << "\", failed" << std::endl;
		return false;
	}

	// Read file into stream
	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();
	if (shaderStream.fail())
	{
		std::cout << "[Utilities.ReadFile] Error - Reading file, \"" << path.string() << "\", failed" << std::endl;
		return false;
	}

	contents = shaderStream.str();
	return true;
}
