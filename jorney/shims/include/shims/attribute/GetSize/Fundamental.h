#pragma once

#include <cstddef>

namespace shims
{
	template<typename T, size_t N>
	inline
	size_t GetSize (const T (&) [N])
	{
		return N;
	}
}
