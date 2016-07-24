#pragma once

#include <cstddef>

namespace shims
{
	template <typename C>
	typename C::const_iterator GetBegin(const C& container)
	{
		return container.begin();
	}

	template <typename C>
	typename C::iterator GetBegin(C& container)
	{
		return container.begin();
	}
}