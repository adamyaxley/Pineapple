/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename B>
B& pa::ListViewIterator<B>::operator*()
{
	return *m_node->dataPtr;
}

template <typename B>
pa::ListViewIterator<B>::ListViewIterator(pa::NodeBase<B>* node) noexcept
	: pa::ListIteratorBase<B>(node)
{
}

template <typename B>
pa::ListViewIterator<B>& pa::ListViewIterator<B>::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

template <typename B>
pa::ListViewIterator<B>& pa::ListViewIterator<B>::operator--()
{
	m_node = m_node->prev;
	return *this;
}

template <typename B>
pa::ListViewIterator<B> pa::ListView<B>::begin() const noexcept
{
	return pa::ListViewIterator<B>(m_begin.next.get());
}

template <typename B>
pa::ListViewIterator<B> pa::ListView<B>::end() const noexcept
{
	return pa::ListViewIterator<B>(m_end);
}

template <typename B>
void pa::ListView<B>::erase(pa::ListViewIterator<B>& position) const
{
	// Verify that we are not erasing the begin or end node,
	PA_ASSERTF(position.m_node->next != m_begin.next, "Cannot erase the begin node marker");
	PA_ASSERTF(position.m_node != m_end, "Cannot erase the end node marker");

	auto node = position.m_node;
	position.m_node = node->next.get();

	node->next->prev = node->prev;
	node->prev->next = std::move(node->next);
}

template <typename B>
void pa::ListView<B>::clear()
{
	auto end = std::move(m_end->prev->next);
	auto node = m_end->prev;

	// Reverse iterate the elements to avoid a potential stack overflow from recursive destructors
	while (node != &m_begin)
	{
		node->next.reset();
		node = node->prev;
	}

	end->prev = node;
	m_begin.next = std::move(end);
}