/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/List.h>

namespace pa
{
	template <typename B>
	class ListViewIterator : public ListIteratorBase<B>,
							 public std::iterator<std::bidirectional_iterator_tag, B, std::ptrdiff_t, B*, B&>
	{
	public:
		friend class ListView<B>;

		ListViewIterator() = default;
		ListViewIterator(const ListViewIterator& copy) = default;
		ListViewIterator(ListViewIterator&& move) = default;
		ListViewIterator& operator=(const ListViewIterator& rhs) = default;

		ListViewIterator& operator++();
		ListViewIterator& operator--();

		B& operator*();

	private:
		explicit ListViewIterator(NodeBase<B>* node) noexcept;
	};

	template <typename B>
	class ListView
	{
	public:
		// Construct from a List
		template <typename T>
		ListView(List<T, B>& list) noexcept
			: m_begin(list.m_begin)
			, m_end(list.m_end)
		{
		}

		ListViewIterator<B> begin() const noexcept;
		ListViewIterator<B> end() const noexcept;

		// Erases the current node, and points the iterator to the next node
		void erase(ListViewIterator<B>& position) const;

		void clear();

	private:
		BeginNodeBase<B>& m_begin;
		NodeBase<B>*& m_end;
	};
}

#include <Pineapple/Engine/Container/ListView.inl>
