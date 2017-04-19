#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>
template < class _T >
class List
{
/* 
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
	Node < typename _T > * head, * tail;
	int _size;
public:
	List();
//	List(List & _List);				// Copy Operator überladen
	~List();
	void InsertFront(typename _T key);		// Einfügen eines Knotens am Anfang
	void InsertBack(typename _T key);		// Einfügen eines Knotesn am Ende
	bool getFront(typename _T & key);		// Entnehmen eines Knoten am Anfang
	bool getBack(typename _T & key);		// Entnehmen eines Knoten am Ende
	bool del(typename _T key);			// löschen eines Knotens [key]
	bool search(typename _T key);			// Suchen eines Knoten
	bool swap(typename _T key1, typename _T key2);	// Knoten in der Liste vertauschen
	int size(void);					// Größe der Lise (Anzahl der Knoten)
	bool test(void);				// Überprüfen der Zeigerstruktur der Liste
	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	List<typename _T> & operator = (const List<typename _T> & _List);						// Zuweisungsoperator definieren
	List<typename _T> & operator = (const List<typename _T> * _List);						// Zuweisungsoperator definieren
	List<typename _T> & operator + (const List<typename _T> & List_Append) const;			// Listen zusammenführen zu einer Liste
	List<typename _T> & operator + (const List<typename _T> * List_Append) const;			// Listen zusammenführen zu einer Liste
	template <class _T> friend std::ostream & operator << (std::ostream & stream, const List<typename _T> & Liste);		// Ausgabeoperator überladen
	template <class _T> friend std::ostream & operator << (std::ostream & stream, const List<typename _T> * Liste);		// Ausgabeoperator überladen
};

template < class _T >
List<typename _T>::List()
{
	head = new Node<typename _T>();
	tail = new Node<typename _T>();
	_size = 0;
	head->next = tail;
	tail->prev = head;
}

template < class _T >
List<typename _T>::~List()
{
	typename _T t;
	while (getBack(t));
}

template < class _T >
void List<typename _T>::InsertFront(typename _T key)
{
	Node<typename _T> *n(new Node<typename _T>(key, head->next, head));
	head->next->prev = n;
	head->next = n;
	++_size;
}

template < class _T >
void List<typename _T>::InsertBack(typename _T key)
{
	Node<typename _T> *n(new Node<typename _T>(key, tail, tail->prev));
	tail->prev->next = n;
	tail->prev = n;
	++_size;
}

template < class _T >
bool List<typename _T>::getFront(typename _T & key)
{
	bool ret(false);
	if (head->next)
	{
		Node<typename _T> *n(head->next);
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

template < class _T >
bool List<typename _T>::getBack(typename _T & key)
{
	bool ret(false);
	if (tail)
	{
		Node<typename _T> *n(tail->prev);
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

template < class _T >
bool List<typename _T>::del(typename _T key)
{
	bool ret(false);
	for (Node<typename _T> *n(head->next); n != tail; n = n->next)
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

template < class _T >
bool List<typename _T>::search(typename _T key)
{
	bool ret(false);
	for (Node<typename _T> *n = head->next; n != tail; n = n->next)
	{
		if (n->key == key)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

template < class _T >
bool List<typename _T>::swap(typename _T key1, typename _T key2)
{
	bool ret(false);
	for (Node<typename _T> *n1(head->next), *n2; n1 != tail; n1 = n1->next)
	{
		if (n1->key == key1)
		{
			for (n2 = head->next; n2 != tail; n2 = n2->next)
			{
				if (n2->key == key2)
				{
					/*typename _T t = n1->key;
					n1->key = n2->key;
					n2->key = t;*/
					Node<typename _T> *tp(n1->prev), *tn(n1->next);
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

template < class _T >
int List<typename _T>::size(void)
{
	return _size;
}

template < class _T >
bool List<typename _T>::test(void)
{
	bool ret(true);
	for (Node<typename _T> *n(head); n != nullptr; n = n->next)
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
		for (Node<typename _T> *n(tail); n != nullptr; n = n->prev)
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

template < class _T >
void List<typename _T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen der Formatierung für den überladenen Streamingoperator <<
	_form.start = start;			// Ausgabe zu Beginn der Liste
	_form.zwischen = zwischen;		// Ausgabe zwischen zwei Knoten
	_form.ende = ende;				// Ausgabe am Ende der Liste
}

template < class _T >
List<typename _T> & List<typename _T>::operator = (const List<typename _T> & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node<typename _T> * tmp_node;
	if (_size)
	{
		Node<typename _T> * tmp_del;
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

template < class _T >
List<typename _T> & List<typename _T>::operator = (const List<typename _T> * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node<typename _T> * tmp_node;
	if (_size)
	{
		Node<typename _T> * tmp_del;
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
	return *this;
}

template < class _T >
List<typename _T> & List<typename _T>::operator + (const List<typename _T> & List_Append) const
{
	List<typename _T> * tmp = new List<typename _T>();
	Node<typename _T> * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail) {
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append._size) return *tmp;
	tmp_node = List_Append.head->next;
	while (tmp_node != List_Append.tail) {
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *tmp;
}

template < class _T >
List<typename _T> & List<typename _T>::operator + (const List<typename _T> * List_Append) const
{
	List<typename _T> * tmp = new List<typename _T>();
	Node<typename _T> * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail) {
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append->_size) return *tmp;
	tmp_node = List_Append->head->next;
	while (tmp_node != List_Append->tail) {
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *tmp;
}

template < class _T >
std::ostream & operator<<(std::ostream  & stream, const List<typename _T> & Liste)
{
	stream << Liste._form.start;
	for (Node<typename _T> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	return stream;
}

template < class _T >
std::ostream & operator << (std::ostream & stream, const List<typename _T> * Liste)
{
	stream << Liste->_form.start;
	for (Node<typename _T> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	return stream;
}
#endif