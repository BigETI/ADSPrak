#include "Tree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	int option(0), alter(0), plz(0), pos_id(0);
	double einkommen(0.0);
	string name, file_name;
	Tree tree;
	vector<TreeNode *> found;
	ifstream ifs;
	size_t rows(0UL);
	wcout << L"====================================\nPerson Analyzer v19.84, by George Orwell\n====================================\n1) Datensatz einfuegen, manuell\n2) Datensatz einfuegen, CSV Datei\n3) Datensatz loeschen\n4) Suchen\n5) Datenstruktur anzeigen";
	while (true)
	{
		wcout << L"\n?> ";
		wcin >> option;
		switch (option)
		{
		case 1:
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
		case 2:
			wcout << L"+ Bitte geben Sie den Dateinamen an\nDateiname ?> ";
			cin >> file_name;
			ifs.open(file_name);
			rows = tree.parseCSV(ifs);
			if (rows > 0UL)
			{
				if (rows == 1UL)
					wcout << L"+ Ihr Datensatz wurde eingefuegt.";
				else
					wcout << L"+ Ihre " << rows << L" Datensaetze wurden eingefuegt.";
			}
			else
				wcout << L"+ Ihre Datensaetze konnten nicht eingefuegt werden.";
			ifs.close();
			break;
		case 3:
			wcout << L"+ Bitte geben Sie den zu loeschenden Datensatz an\nPosID: ";
			cin >> pos_id;
			if (tree.remove(pos_id))
				wcout << L"+ Datensatz wurde geloescht.";
			else
				wcout << L"+ Datensatz konnte nicht geloescht werden.";
			break;
		case 4:
			wcout << L"+ Bitte geben Sie den zu suchenden Datensatz an\nName ?> ";
			cin >> name;
			wcout << L"+ Fundstellen:\n";
			tree.search(name, found);
			for (vector<TreeNode *>::iterator it(found.begin()), end(found.end()); it != end; ++it)
				cout << (*it)->toString();
			break;
		case 5:
			cout << tree.toString();
			break;
		}
	}
	return 0;
}