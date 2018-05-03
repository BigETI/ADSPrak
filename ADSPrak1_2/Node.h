#ifndef _NODE_H
#define _NODE_H
template < typename _T >
class Node
{
public:
	typename _T key;
	Node < typename _T > * next, *prev;
public:
	Node()
	{
		//key = 0;
		next = nullptr;
		prev = nullptr;
	}

	Node(typename _T key, Node < typename _T > * next = nullptr, Node < typename _T > * prev = nullptr)
	{
		this->key = key;
		this->next = next;
		this->prev = prev;
	}

	~Node()
	{
		//
	}
};
#endif
