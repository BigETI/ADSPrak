#include "Node.h"
Node::Node()
{
	key = 0;
	next = 0;
	prev = 0;
}
Node::Node(int key, Node * next, Node * prev)
{
	this->key = key;
	this->next = next;
	this->prev = prev;
}
Node::~Node()
{
}
