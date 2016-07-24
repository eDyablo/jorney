#pragma once

#include <vector>

namespace shims
{
	template <typename Char>
	const Char* GetCString (const std::vector<Char>& src)
	{
		return &src[0];
	}
}
