#pragma once

#include <cstddef>

namespace shims
{
	template<typename T, size_t N>
	inline
	const T* GetBegin(const T (&array) [N])
	{
		return &array[0];
	}

	template<typename T, size_t N>
	inline
	T* GetBegin(T (&array) [N])
	{
		return &array[0];
	}
}