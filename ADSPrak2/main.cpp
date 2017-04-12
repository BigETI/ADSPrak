#include <iostream>
#include "Ringpuffer.h"

using namespace std;

int main(int argc, char *argv[])
{
	Ringpuffer ringpuffer;
	int option(0);
	string description, data;
	RingNode *s;
	wcout << L"==================================\n OneRingToRuleThemAll v0.1, by Sauron Schmidt\n==================================\n1) Backup einfuegen\n2) Backup suchen\n3) Alle Backups ausgeben";
	while (true)
	{
		wcout << L"\n?> ";
		wcin >> option;
		switch (option)
		{
		case 1:
			wcout << L"+Neuen Datensatz einfuegen\nBeschreibung ?> ";
			cin >> description;
			wcout << L"Daten ?> ";
			cin >> data;
			if (ringpuffer.addNode(description, data))
				wcout << L"+Ihr Datensatz wurde hinzugefuegt.";
			break;
		case 2:
			wcout << L"+Nach welchen Daten soll gesucht werden?\n?> ";
			cin >> data;
			s = ringpuffer.search(data);
			if (s)
			{
				wcout << "+ Gefunden in Backup: ";
				s->print();
			}
			else
				wcout << "+ Backup nicht gefunden.";
			break;
		case 3:
			ringpuffer.print();
			break;
		default:
			wcout << L"Option " << option << L" ist nicht definiert!";
		}
		wcout << L"\n[...]";
	}
	return 0;
}