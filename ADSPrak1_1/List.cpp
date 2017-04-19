#include "List.h"
List::List()
{
	head = new Node;
	tail = new Node;
	_size = 0;
	head->next = tail;
	tail->prev = head;
}
List::~List()
{
	int t;
	while (getBack(t));
}
void List::InsertFront(int key)
{
	Node *n(new Node(key, head->next, head));
	head->next->prev = n;
	head->next = n;
	++_size;
}
void List::InsertBack(int key)
{
	Node *n(new Node(key, tail, tail->prev));
	tail->prev->next = n;
	tail->prev = n;
	++_size;
}
bool List::getFront(int & key)
{
	bool ret(false);
	if (head->next)
	{
		Node *n(head->next);
		if (n != tail)
		{
			head->next = n->next;
			n->next->prev = head;
			key = n->key;
			delete n;
			--_size;
		}
	}
	return ret;
}
bool List::getBack(int & key)
{
	bool ret(false);
	if (tail)
	{
		Node *n(tail->prev);
		if (n != head)
		{
			tail->prev = n->prev;
			n->prev->next = tail;
			key = n->key;
			delete n;
			--_size;
			ret = true;
		}
	}
	return ret;
}
bool List::del(int key)
{
	bool ret(false);
	for (Node *n(head->next); n != tail; n = n->next)
	{
		if (n->key == key)
		{
			n->prev->next = n->next;
			n->next->prev = n->prev;
			delete n;
			--_size;
			ret = true;
			break;
		}
	}
	return ret;
}
bool List::search(int key)
{
	bool ret(false);
	for (Node *n = head->next; n != tail; n = n->next)
	{
		if (n->key == key)
		{
			ret = true;
			break;
		}
	}
	return ret;
}
bool List::swap(int key1, int key2)
{
	bool ret(false);
	for (Node *n1(head->next), *n2; n1 != tail; n1 = n1->next)
	{
		if (n1->key == key1)
		{
			for (n2 = head->next; n2 != tail; n2 = n2->next)
			{
				if (n2->key == key2)
				{
					Node *tp(n1->prev), *tn(n1->next);
					/*int t = n1->key;
					n1->key = n2->key;
					n2->key = t;*/
					if (n1->prev != head)
						n1->prev->next = n2;
					if (n1->next != tail)
						n1->next->prev = n2;
					if (n2->prev != head)
						n2->prev->next = n1;
					if (n2->next != tail)
						n2->next->prev = n2;
					n1->prev = n2->prev;
					n1->next = n2->next;
					n2->prev = tp;
					n2->next = tn;
					ret = true;
					break;
				}
			}
			break;
		}
	}
	return ret;
}
int List::size(void)
{
	return _size;
}
bool List::test(void)
{
	bool ret(true);
	for (Node *n(head); n != nullptr; n = n->next)
	{
		if (n == tail)
		{
			if (n->next)
			{
				ret = false;
				break;
			}
		}
	}
	if (ret)
	{
		for (Node *n(tail); n != nullptr; n = n->prev)
		{
			if (n == head)
			{
				if (n->prev)
				{
					ret = false;
					break;
				}
			}
		}
	}
	return ret;
}
void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen der Formatierung für den überladenen Streamingoperator <<
	_form.start = start;			// Ausgabe zu Beginn der Liste
	_form.zwischen = zwischen;		// Ausgabe zwischen zwei Knoten
	_form.ende = ende;				// Ausgabe am Ende der Liste
}
List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == & _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List.head->next;
	while (tmp_node != _List.tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *this;
}
List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{	
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List->head->next;
	while (tmp_node != _List->tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return * this;
}
List & List::operator + (const List & List_Append) const
{
	List * tmp = new List;
	Node * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append._size) return * tmp;
	tmp_node = List_Append.head->next;
	while (tmp_node != List_Append.tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return * tmp;
}
List & List::operator + (const List * List_Append) const
{
	List * tmp = new List;
	Node * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append->_size) return *tmp;
	tmp_node = List_Append->head->next;
	while (tmp_node != List_Append->tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *tmp;
}
std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	stream << Liste._form.start;
	for (Node * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	return stream;
}
std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	stream << Liste->_form.start;
	for (Node * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	return stream;
}