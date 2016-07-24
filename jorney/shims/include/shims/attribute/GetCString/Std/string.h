#pragma once

#include <string>

namespace shims
{
	template <typename Char>
	const Char* GetCString (const std::basic_string<Char>& src)
	{
		return src.c_str ();
	}
}
