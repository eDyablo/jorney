#pragma once

#include <cstddef>

namespace shims
{
	template <typename C>
	typename C::const_iterator GetEnd(const C& container)
	{
		return container.end();
	}

	template <typename C>
	typename C::iterator GetEnd(C& container)
	{
		return container.end();
	}
}