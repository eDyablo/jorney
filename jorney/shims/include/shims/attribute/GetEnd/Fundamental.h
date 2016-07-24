#pragma once

#include <cstddef>

namespace shims
{
	template<typename T, size_t N>
	inline
	const T* GetEnd (const T (&array) [N])
	{
		return &array[N];
	}

	template<typename T, size_t N>
	inline
	T* GetEnd (T (&array) [N])
	{
		return &array[N];
	}
}