/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/DynamicPool.h>

namespace pa
{
	template <typename B>
	struct NodeBase;

	template <typename B>
	struct BeginNodeBase
	{
		Pool::Ptr<NodeBase<B>> next;
	};

	template <typename B>
	struct NodeBase : public BeginNodeBase<B>
	{
		NodeBase() = default;
		NodeBase(const NodeBase& copy) = default;
		NodeBase(NodeBase&& move) = default;
		NodeBase& operator=(const NodeBase& rhs) = default;
		virtual ~NodeBase()
		{
		}

		NodeBase* prev;
		B* dataPtr;
	};

	template <typename B>
	class ListIteratorBase
	{
	public:
		ListIteratorBase() = default;
		ListIteratorBase(const ListIteratorBase& copy) = default;
		ListIteratorBase(ListIteratorBase&& move) = default;
		ListIteratorBase& operator=(const ListIteratorBase& rhs) = default;

		bool operator==(const ListIteratorBase& rhs) const noexcept;
		bool operator!=(const ListIteratorBase& rhs) const noexcept;

	protected:
		explicit ListIteratorBase(NodeBase<B>* node) noexcept;

		NodeBase<B>* m_node;
	};

	template <typename T, typename B>
	class List;

	template <typename T, typename B = T>
	class ListIterator : public ListIteratorBase<B>,
						 public std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
	{
	public:
		friend class List<T, B>;

		ListIterator() = default;
		ListIterator(const ListIterator& copy) = default;
		ListIterator(ListIterator&& move) = default;
		ListIterator& operator=(const ListIterator& rhs) = default;

		ListIterator& operator++();
		ListIterator& operator--();

		T& operator*();

	private:
		explicit ListIterator(NodeBase<B>* node) noexcept;
	};

	template <typename B>
	class ListView;

	template <typename T, typename B = T>
	class List
	{
	private:
		friend ListView<B>;
		friend ListIterator<T, B>;

		struct Node : public NodeBase<B>
		{
			~Node()
			{
			}
			template <typename... Args>
			Node(Args&&... args);

			T data; //<todo> specialise for T = B or T*
		};

	public:
		List();
		List(std::size_t size);
		List(std::initializer_list<T> list);
		~List();

	public:
		template <typename... Args>
		ListIterator<T, B> emplaceFront(Args&&... args);

		template <typename... Args>
		ListIterator<T, B> emplaceBack(Args&&... args);

		// Inserts an element before position
		template <typename... Args>
		ListIterator<T, B> insert(ListIterator<T, B> position, Args&&... args);

		ListIterator<T, B> begin() const noexcept;
		ListIterator<T, B> end() const noexcept;

		// Erases the current node, and points the iterator to the next node
		void erase(ListIterator<T, B>& position) const;

		const T& front() const noexcept;
		T& front() noexcept;

		const T& back() const noexcept;
		T& back() noexcept;

		void reserve(std::size_t size);

		std::size_t getSize() const noexcept;

		void clear();

	private:
		PA_FORCE_INLINE void createBeginAndEnd();

		// A flat pool of nodes for fast allocation, must come before m_end as m_end is acquired from
		// this pool and must be cleaned up last
		DynamicPool m_pool;

		// The begin node marker, initially has its next pointer set to the end node marker
		BeginNodeBase<B> m_begin;

		// The end node marker, initially has its prev pointer set to the begin node marker
		NodeBase<B>* m_end;
	};
}

#include <Pineapple/Engine/Container/List.inl>
