#pragma once

namespace pa
{
	template <typename T>
	class EnableChildList
	{
	public:
		EnableChildList(T* parent)
		{
			parent->getWorld().registerPostConstructionObjectTransform([](std::shared_ptr<pa::Object> object) {
				object->getWorld().registerChild(std::static_pointer_cast<T, pa::Object>(object)); });
		}
	};
}