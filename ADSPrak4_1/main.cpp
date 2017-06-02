#include <iostream>
#include <string>
#include "Graph.h"

#define SEARCH_ITERATIVE

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void displayMenu()
{
	std::cout << "Working on Graphs. Please choose:" << std::endl
		<< "1) Graph einlesen" << std::endl
		<< "2) Tiefensuche" << std::endl
		<< "3) Breitensuche " << std::endl
		<< "4) Prim" << std::endl
		<< "5) Kruskal" << std::endl
		<< "6) Print Graph as nodelist" << std::endl
		<< "0) for quit" << std::endl
		<< "?> ";
}

void print_nodes(std::vector<GraphNode *> & nodes)
{
	bool first(true);
	for (std::vector<GraphNode *>::iterator it(nodes.begin()), end(nodes.end()); it != end; ++it)
	{
		if (first)
		{
			first = false;
			std::cout << "Nodes: ";
		}
		else
			std::cout << " -> ";
		std::cout << "[" << (*it)->_key << "]";
	}
	if (first)
		std::cout << "No nodes";
	std::cout << std::endl;
}

int main() {


	//Insert a switch-case to call your algorithms
	//Maybe you can copy from older Projects
	Graph* myGraph = new Graph();
	std::string path;
	int menuwahl = -1;
	int key = -1;
	std::vector<GraphNode *> result_nodes;

	while (menuwahl != 0) {

		do {
			displayMenu();
			std::cin >> menuwahl;
		} while (menuwahl > 6 || menuwahl < 0);

		switch (menuwahl)
		{
			//Read Graph
		case 1:
		{
			std::string path;
			std::cout << "Insert path of Graphfile: " << std::endl;
			std::cin >> path;

			bool done = myGraph->init(path);

			if (done)
				std::cout << "Initialize graph successful" << std::endl;
			else
				std::cout << "Cannot read file" << std::endl;
		}
		break;

		//Depthsearch
		case 2:
			std::cout << "Choose a startkey: " << std::endl;
			std::cin >> key;
			std::cout << (
#ifdef SEARCH_ITERATIVE
				//This way:
				myGraph->depthSearchIter(key, result_nodes)
#else
				//Or this:
				myGraph->depthSearchRek(key, result_nodes)
#endif
				? "Ja" : "Nein") << std::endl;
			print_nodes(result_nodes);
			break;

			//Breadthsearch
		case 3:
			std::cout << "Choose a startkey: " << std::endl;
			std::cin >> key;
			std::cout << (
#ifdef SEARCH_ITERATIVE
				//This way:
				myGraph->breadthSearchIter(key, result_nodes)
#else
				//Or this:
				myGraph->breadthSearchRek(key, result_nodes)
#endif
				? "Ja" : "Nein") << std::endl;
			print_nodes(result_nodes);
			break;

			//Prim
		case 4:
			std::cout << "Choose a startkey: " << std::endl;
			std::cin >> key;
			std::cout << "Tree weight: " << myGraph->prim(key) << std::endl;
			break;

			//Kruskal
		case 5:
			std::cout << "Tree weight: " << myGraph->kruskal() << std::endl;
			break;
			//Print function
		case 6:
		{
			bool done = myGraph->print();

			if (done)
				std::cout << "Print graph successful" << std::endl;
			else
				std::cout << "Not able to print" << std::endl;
		}
		break;

		//Quit
		case 0:
			delete myGraph;
			break;
		}
	}

	return 0;
}
