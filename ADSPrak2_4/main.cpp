#include <iostream>
#include "Ringpuffer.h"

using namespace std;

int main(int argc, char *argv[])
{
	int option(0), alter(0), plz(0), pos_id(0);
	Tree tree;
	Ringpuffer ringpuffer;
	string description, name;
	RingNode *n(nullptr);
	vector<RingNode *> backups;
	double einkommen(0.0);
	vector<TreeNode *> found;
	wcout << L"====================================\nHPDS v0.1, by Speedy Gonzales\n====================================\nBackupsteuerung:\n1) Backup einfuegen\n2) Backup suchen\n3) Alle Backups ausgeben\n------------------------------\nAktueller Baum:\n4) Datensatz einfuegen\n5) Datensatz loeschen\n6) Suchen\n7) Datenstruktur anzeigen";
	while (true)
	{
		wcout << L"\n?> ";
		wcin >> option;
		switch (option)
		{
		case 1:
			wcout << L"+ Bitte geben Sie die Beschreibung des Backups an\nBeschreibung ?> ";
			cin >> description;
			if (ringpuffer.addNode(description, tree))
				cout << "+ Backup \"" << description << " wurde erstellt.";
			else
				wcout << L"+ Backup konnte nicht erstellt werden.";
			break;
		case 2:
			wcout << L"+ Bitte geben Sie die zu suchende Backup Beschreibung an\nBeschreibung ?> ";
			cin >> description;
			n = ringpuffer.search(description);
			if (n)
			{
				cout << "+ Backup wurde gefunden.\n";
				n->print();
			}
			else
				wcout << L"+ Backup wurde nicht gefunden.";
			break;
		case 3:
			ringpuffer.getAll(backups);
			wcout << L"+ Gebe alle Backups aus:";
			for (vector<RingNode *>::iterator it(backups.begin()), end(backups.end()); it != end; ++it)
			{
				cout << std::endl;
				(*it)->print();
			}
			break;
		case 4:
			wcout << L"+ Bitte geben Sie die den Datensatz ein\nName ?> ";
			cin >> name;
			wcout << L"Alter ?> ";
			cin >> alter;
			wcout << L"Einkommen ?> ";
			cin >> einkommen;
			wcout << L"PLZ ?> ";
			cin >> plz;
			if (tree.addNode(name, alter, einkommen, plz))
				wcout << L"+ Ihr Datensatz wurde eingefuegt.";
			else
				wcout << L"+ Ihr Datensatz konnte nicht eingefuegt werden.";
			break;
		case 5:
			wcout << L"+ Bitte geben Sie den zu loeschenden Datensatz an\nPosID: ";
			cin >> pos_id;
			if (tree.remove(pos_id))
				wcout << L"+ Datensatz wurde geloescht.";
			else
				wcout << L"+ Datensatz konnte nicht geloescht werden.";
			break;
		case 6:
			wcout << L"+ Bitte geben Sie den zu suchenden Datensatz an\nName ?> ";
			cin >> name;
			wcout << L"+ Fundstellen:\n";
			tree.search(name, found);
			for (vector<TreeNode *>::iterator it(found.begin()), end(found.end()); it != end; ++it)
				cout << (*it)->toString();
			break;
		case 7:
			cout << tree.toString();
			break;
		}
	}
	return 0;
}