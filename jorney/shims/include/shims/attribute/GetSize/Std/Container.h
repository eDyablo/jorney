#pragma once

#include <cstddef>

namespace shims
{
	template <typename C>
	size_t GetSize (const C& container)
	{
		return container.size ();
	}
}
