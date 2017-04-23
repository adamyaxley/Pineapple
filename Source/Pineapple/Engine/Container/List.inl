/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename B>
bool pa::ListIteratorBase<B>::operator==(const pa::ListIteratorBase<B>& rhs) const noexcept
{
	return !operator!=(rhs);
}

template <typename B>
bool pa::ListIteratorBase<B>::operator!=(const pa::ListIteratorBase<B>& rhs) const noexcept
{
	return m_node != rhs.m_node;
}

template <typename B>
pa::ListIteratorBase<B>::ListIteratorBase(pa::NodeBase<B>* node) noexcept
	: m_node(node)
{
}

template <typename T, typename B>
pa::ListIterator<T, B>::ListIterator(pa::NodeBase<B>* node) noexcept
	: pa::ListIteratorBase<B>(node)
{
}

template <typename T, typename B>
pa::ListIterator<T, B>& pa::ListIterator<T, B>::operator++()
{
	this->m_node = this->m_node->next.get();
	return *this;
}

template <typename T, typename B>
pa::ListIterator<T, B>& pa::ListIterator<T, B>::operator--()
{
	this->m_node = this->m_node->prev;
	return *this;
}

template <typename T, typename B>
T& pa::ListIterator<T, B>::operator*()
{
	return static_cast<typename pa::List<T, B>::Node*>(this->m_node)->data;
}

template <typename T, typename B>
template <typename... Args>
pa::List<T, B>::Node::Node(Args&&... args)
	: data(std::forward<Args>(args)...)
{
	// Assign the base B pointer to the derived T. This must be done after data has been
	// constructed if T has a virtual base.
	this->dataPtr = &data;
}

template <typename T, typename B>
pa::List<T, B>::List()
	: pa::List<T, B>(16)
{
}

template <typename T, typename B>
pa::List<T, B>::List(std::size_t size)
	: m_pool(sizeof(pa::List<T, B>::Node), size + 1)
{
	createBeginAndEnd();
}

template <typename T, typename B>
pa::List<T, B>::List(std::initializer_list<T> list)
	: m_pool(sizeof(pa::List<T, B>::Node), list.size() + 1)
{
	createBeginAndEnd();

	for (auto&& item : list)
	{
		emplaceBack(item);
	}
}

template <typename T, typename B>
pa::List<T, B>::~List()
{
	clear();
}

template <typename T, typename B>
void pa::List<T, B>::clear()
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

template <typename T, typename B>
template <typename... Args>
pa::ListIterator<T, B> pa::List<T, B>::emplaceFront(Args&&... args)
{
	return pa::ListIterator<T, B>(insert(pa::ListIterator<T, B>(m_begin.next.get()), std::forward<Args>(args)...));
}

template <typename T, typename B>
template <typename... Args>
pa::ListIterator<T, B> pa::List<T, B>::emplaceBack(Args&&... args)
{
	return pa::ListIterator<T, B>(insert(pa::ListIterator<T, B>(m_end), std::forward<Args>(args)...));
}

template <typename T, typename B>
template <typename... Args>
pa::ListIterator<T, B> pa::List<T, B>::insert(pa::ListIterator<T, B> position, Args&&... args)
{
	auto node = m_pool.acquire<pa::List<T, B>::Node>(std::forward<Args>(args)...);
	auto previous = static_cast<pa::BeginNodeBase<B>*>(position.m_node->prev);

	position.m_node->prev = node.get();
	node->next = std::move(previous->next);
	node->prev = static_cast<pa::List<T, B>::Node*>(previous);
	previous->next = std::move(node);

	return pa::ListIterator<T, B>(position.m_node->prev);
}

template <typename T, typename B>
pa::ListIterator<T, B> pa::List<T, B>::begin() const noexcept
{
	return pa::ListIterator<T, B>(m_begin.next.get());
}

template <typename T, typename B>
pa::ListIterator<T, B> pa::List<T, B>::end() const noexcept
{
	return pa::ListIterator<T, B>(m_end);
}

template <typename T, typename B>
pa::ListIterator<T, B> pa::List<T, B>::erase(pa::ListIterator<T, B> position) const
{
	// Verify that we are not erasing the begin or end node,
	PA_ASSERTF(position.m_node->next != m_begin.next, "Cannot erase the begin node marker");
	PA_ASSERTF(position.m_node != m_end, "Cannot erase the end node marker");

	auto node = position.m_node;
	position.m_node = node->next.get();

	node->next->prev = node->prev;
	node->prev->next = std::move(node->next);

	return position;
}

template <typename T, typename B>
const T& pa::List<T, B>::front() const noexcept
{
	PA_ASSERTF(getSize() > 0, "List is empty");
	return *begin();
}

template <typename T, typename B>
T& pa::List<T, B>::front() noexcept
{
	PA_ASSERTF(getSize() > 0, "List is empty");
	return *begin();
}

template <typename T, typename B>
const T& pa::List<T, B>::back() const noexcept
{
	PA_ASSERTF(getSize() > 0, "List is empty");
	return *pa::ListIterator<T, B>(m_end->prev);
}

template <typename T, typename B>
T& pa::List<T, B>::back() noexcept
{
	PA_ASSERTF(getSize() > 0, "List is empty");
	return *pa::ListIterator<T, B>(m_end->prev);
}

template <typename T, typename B>
void pa::List<T, B>::reserve(std::size_t size)
{
	m_pool.reserve(size);
}

template <typename T, typename B>
std::size_t pa::List<T, B>::getSize() const noexcept
{
	return m_pool.getCapacity() - m_pool.getSize() - 1;
}

template <typename T, typename B>
PA_FORCE_INLINE void pa::List<T, B>::createBeginAndEnd()
{
	auto end = m_pool.acquire<pa::NodeBase<B>>();
	m_end = end.get();

	m_begin.next = std::move(end);
	m_begin.next->prev = static_cast<pa::NodeBase<B>*>(&m_begin);
}
