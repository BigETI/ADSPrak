#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>
class List 
{
/* 
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
	Node * head, * tail;
	int _size;
public:
	List();
//	List(List & _List);				// Copy Operator �berladen
	~List();
	void InsertFront(int key);		// Einf�gen eines Knotens am Anfang
	void InsertBack(int key);		// Einf�gen eines Knotesn am Ende
	bool getFront(int & key);		// Entnehmen eines Knoten am Anfang
	bool getBack(int & key);		// Entnehmen eines Knoten am Ende
	bool del(int key);			// l�schen eines Knotens [key]
	bool search(int key);			// Suchen eines Knoten
	bool swap(int key1, int key2);	// Knoten in der Liste vertauschen
	int size(void);					// Gr��e der Lise (Anzahl der Knoten)
	bool test(void);				// �berpr�fen der Zeigerstruktur der Liste
	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	List & operator = (const List & _List);						// Zuweisungsoperator definieren
	List & operator = (const List * _List);						// Zuweisungsoperator definieren
	List & operator + (const List & List_Append) const;			// Listen zusammenf�hren zu einer Liste
	List & operator + (const List * List_Append) const;			// Listen zusammenf�hren zu einer Liste
	friend std::ostream & operator << (std::ostream & stream, List const & Liste);		// Ausgabeoperator �berladen
	friend std::ostream & operator << (std::ostream & stream, List const * Liste);		// Ausgabeoperator �berladen
};
#endif