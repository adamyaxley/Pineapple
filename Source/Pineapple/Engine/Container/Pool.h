/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/IndexBuffer.h>

#include <functional>
#include <memory>

namespace pa
{
	class Pool
	{
	private:
		template <typename T>
		class Deleter
		{
		public:
			Deleter()
			{
			}
			~Deleter()
			{
			}

			template <typename U>
			Deleter(const Deleter<U>& convert);

			Deleter(Pool* pool);

			void operator()(T* object);

			Pool* m_pool;
		};

	public:
		template <typename T>
		using Ptr = std::unique_ptr<T, Deleter<T>>;

		template <typename T>
		friend class Deleter;

		Pool() = delete;
		Pool(const Pool& copy) = delete;
		Pool(Pool&& move) = delete;
		Pool(std::size_t maxObjectSize, std::size_t size);
		~Pool();

		template <typename T, typename... Args>
		Ptr<T> acquire(Args&&... args);

		int getSize() const noexcept;
		int getCapacity() const noexcept;

	private:
		template <typename T>
		void release(T* object);

		const std::size_t m_maxObjectSize;
		IndexBuffer m_indexBuffer;
		std::uint8_t* m_objects; // Must be aligned properly for T
	};
}

#include <Pineapple/Engine/Container/Pool.inl>
