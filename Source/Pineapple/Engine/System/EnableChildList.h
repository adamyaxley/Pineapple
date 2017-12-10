#pragma once

namespace pa
{
	class World;
	
	template <typename T>
	class EnableChildList
	{
	public:
		EnableChildList(World& world)
		{
			world.registerPostConstructionObjectTransform([](std::shared_ptr<pa::Object> object) {
				object->getWorld().registerChild(std::static_pointer_cast<T, pa::Object>(object)); });
		}
	};
}