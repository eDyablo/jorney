#pragma once

namespace shims
{
	template <typename C>
	bool IsEmpty (const C& container)
	{
		return container.empty ();
	}
}
