#pragma once

#include <memory>

namespace shims
{
	template <typename Type>
	Type* GetRawPtr (std::auto_ptr<Type>& ptr)
	{
		return ptr.get ();
	}

	template <typename Type>
	const Type* GetRawPtr (const std::auto_ptr<Type>& ptr)
	{
		return ptr.get ();
	}
}
