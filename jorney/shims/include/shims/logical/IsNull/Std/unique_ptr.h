#pragma once

#include <memory>

namespace shims
{
	template <typename Type>
	bool IsNull (const std::unique_ptr<Type>& ptr)
	{
		return ptr.get () == nullptr;
	}
}
