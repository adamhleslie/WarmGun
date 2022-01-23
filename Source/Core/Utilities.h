#pragma once

#include <cstddef>
#include <array>
#include <tuple>
#include <string>
#include <filesystem>

namespace Utilities
{
	bool ReadFile(const std::filesystem::path& path, std::string& contents);

	#pragma region CArray
	// CArray is a tuple storing an array's pointer, and the size of the array in bytes
	// Recommended unpacking:
	//     auto [data, sizeOf] = x;
	template<class T>
	using CArray = std::tuple<T*, std::size_t>;

	template<class T>
	CArray<T> ToCArray(T* data, std::size_t size)
	{
		return {data, (sizeof(T) * size)};
	}

	template<class T, std::size_t N>
	std::size_t SizeOfData(const std::array<T, N>& array)
	{
		return (sizeof(T) * N);
	}

	template<class T, std::size_t N>
	CArray<T> ToCArray(std::array<T, N>& array)
	{
		return std::tuple{array.data(), SizeOfData(array)};
	}

	template<class T, std::size_t N>
	CArray<const T> ToCArray(const std::array<T, N>& array)
	{
		return std::tuple{array.data(), SizeOfData(array)};
	}

	template<class T>
	std::size_t GetSize(CArray<T> array)
	{
		return (std::get<1>(array) / sizeof(T));
	}
	#pragma endregion
}
