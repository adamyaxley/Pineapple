#pragma once

namespace pa
{
	namespace IOS
	{
		template <typename Function>
		auto withAutoreleasePool(Function&& function) -> decltype(function())
		{
			@autoreleasepool
			{
				return function();
			}
		}
	}
}
