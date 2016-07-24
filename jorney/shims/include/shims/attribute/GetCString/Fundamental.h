#pragma once

namespace shims
{
	template <typename Char>
	const Char* GetCString (const Char* src)
	{
		return src;
	}
}
