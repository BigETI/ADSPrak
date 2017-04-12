#ifndef _NODE_H
#	define _NODE_H
template < typename _T >
class Node
{
public:
	typename _T key;
	Node < typename _T > * next, * prev;
public:
	Node();
	Node(typename _T key, Node<typename _T> * next = 0, Node<typename _T> * prev = 0);
	~Node();
};

template < class _T >
Node<typename _T>::Node()
{
	//key = 0;
	next = 0;
	prev = 0;
}

template < class _T >
Node<typename _T>::Node(typename _T key, Node<typename _T> * next, Node<typename _T> * prev)
{
	this->key = key;
	this->next = next;
	this->prev = prev;
}

template < class _T >
Node<typename _T>::~Node()
{
	//
}

#endif