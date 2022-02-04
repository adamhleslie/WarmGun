#pragma once

#include <string>
#include <filesystem>

namespace Utilities
{
	bool ReadFile(const std::filesystem::path& path, std::string& contents);
}
