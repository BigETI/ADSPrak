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
	Node < typename _T > * head, *tail;			// Zeiger auf Kopf- und End-Element
	int _size;						// Länge der Kette
	bool temp;						// normalerweise false; ist true, wenn es sich um eine temoräre Liste handelt
									// die innerhalb der überladenen Operatoren angelegt wird
public:
	List()
	{
		head = new Node<typename _T>();
		tail = new Node<typename _T>();
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}

	~List()
	{
		typename _T t;
		while (getBack(t));
	}

	void InsertFront(typename _T key)		// Einfügen eines Knotens am Anfang
	{
		Node<typename _T> *n(new Node<typename _T>(key, head->next, head));
		head->next->prev = n;
		head->next = n;
		++_size;
	}

	void InsertBack(typename _T key)		// Einfügen eines Knotesn am Ende
	{
		Node<typename _T> *n(new Node<typename _T>(key, tail, tail->prev));
		tail->prev->next = n;
		tail->prev = n;
		++_size;
	}

	bool getFront(typename _T & key)		// Entnehmen eines Knoten am Anfang
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

	bool getBack(typename _T & key)		// Entnehmen eines Knoten am Ende
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

	bool del(typename _T key)				// löschen eines Knotens [key]
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

	bool search(typename _T key)			// Suchen eines Knoten
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

	bool swap(typename _T key1, typename _T key2)	// Knoten in der Liste vertauschen
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

	int size(void)					// Größe der Lise (Anzahl der Knoten)
	{
		return _size;
	}

	bool test(void)				// Überprüfen der Zeigerstruktur der Liste
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

	void format(const std::string & start, const std::string & zwischen, const std::string & ende)	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	{
		// Setzen der Formatierung für den überladenen Streamingoperator <<
		_form.start = start;			// Ausgabe zu Beginn der Liste
		_form.zwischen = zwischen;		// Ausgabe zwischen zwei Knoten
		_form.ende = ende;				// Ausgabe am Ende der Liste
	}

	List<typename _T> & operator = (const List<typename _T> & _List)						// Zuweisungsoperator definieren
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

	List<typename _T> & operator = (const List<typename _T> * _List)						// Zuweisungsoperator definieren
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

	List<typename _T> & operator + (const List<typename _T> & List_Append)				// Listen zusammenführen zu einer Liste
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

	List<typename _T> & operator + (const List<typename _T> * List_Append)				// Listen zusammenführen zu einer Liste
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

	friend std::ostream & operator << (std::ostream & stream, List<typename _T> const & Liste)		// Ausgabeoperator überladen
	{
		stream << Liste._form.start;
		for (Node<typename _T> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
			stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
		return stream;
	}

	friend std::ostream & operator << (std::ostream & stream, List<typename _T> const * Liste)		// Ausgabeoperator überladen
	{
		stream << Liste->_form.start;
		for (Node<typename _T> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		{
			stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
		}
		return stream;
	}
};
#endif