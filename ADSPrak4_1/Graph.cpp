#include "Graph.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <functional>
#include <set>

Graph::Graph()
{
	_anzKnoten = 0;
	_nodes.clear();
}

Graph::~Graph()
{
	clear();
}

//Get the node pointer by given key
GraphNode* Graph::GetNodeByKey(int key)
{
	for (int i = 0; i < _anzKnoten; i++)
	{
		GraphNode* currentNode = _nodes[i];
		if (currentNode->_key == key)
		{
			return currentNode;
		}
	}
	return nullptr;
}

//iterate all nodes and set _visited to false
void Graph::setAllUnvisited()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		GraphNode* currentNode = _nodes[i];
		currentNode->_visited = false;
	}
}

//Check if all nodes are set to visited
bool Graph::checkVisited()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		GraphNode* currentNode = _nodes[i];
		if (currentNode->_visited == false)
			return false;
	}
	return true;
}

bool Graph::init(std::string path)
{
	bool ret(false);
	std::ifstream file;
	file.open(path, std::ios_base::in);
	clear();
	if (file.is_open())
	{
		std::cout << "Start reading" << std::endl;

		std::string line;
		std::getline(file, line);
		std::istringstream iss(line);

		std::cout << "Insert _anzKnoten" << std::endl;
		iss >> _anzKnoten;

		std::cout << "Create all Nodes" << std::endl;
		//Alle Knoten anlegen
		for (int i = 0; i < _anzKnoten; i++)
		{
			GraphNode *currentNode = new GraphNode(i);
			_nodes.push_back(currentNode);
		}

		std::cout << "Start creating edges" << std::endl;
		while (std::getline(file, line))
		{
			std::istringstream edges(line);
			int from, value, to;
			if (!(edges >> from >> to >> value)) { break; } // error

			std::cout << "From: " << from << " To: " << to << " Value: " << value << std::endl;
			GraphNode *currentNode = GetNodeByKey(from);
			GraphNode *currentNeighbour = GetNodeByKey(to);
			//Hinrichtung:
			GraphNode::edge edge(currentNeighbour, value);
			currentNode->_edges.push_back(edge);
			//Rückrichtung:
			GraphNode::edge backEdge(currentNode, value);
			currentNeighbour->_edges.push_back(backEdge);
		}
		ret = true;
	}
	else
		std::cout << "Cannot open file." << std::endl;
	return ret;

}

bool Graph::print()
{
	if (_nodes.empty()) return false;
	//Print with Node ID: 1st neighbour, 2nd neighbour ...
	for (int i = 0; i < _anzKnoten; i++)
	{
		GraphNode* currentNode = _nodes[i];
		std::cout << currentNode->_key << " ";
		for (int k = 0; k < currentNode->_edges.size(); k++)
		{
			if (!currentNode->_edges.empty()) {
				GraphNode::edge currentEdge = currentNode->_edges[k];
				std::cout << " -> " << currentEdge.node->_key << " [" << currentEdge.value << "] ";
			}
		}
		std::cout << std::endl;

	}

	return true;
}

void Graph::clear()
{
	for (std::vector<GraphNode *>::iterator it(_nodes.begin()), end(_nodes.end()); it != end; ++it)
		delete *it;
	_nodes.clear();
	_anzKnoten = 0;
}

//Implement here the depth-/breadfirstthsearch and Prim & Kruskal

//Implement this:

void inDepthsearchRek(int startKey, GraphNode *node, std::vector<GraphNode *> & result)
{
	if (!(node->_visited))
	{
		result.push_back(node);
		node->_visited = true;
		for (std::vector<GraphNode::edge>::iterator it(node->_edges.begin()), end(node->_edges.end()); it != end; ++it)
			inDepthsearchRek(startKey, it->node, result);
	}
}

void Graph::depthSearchRek(int startKey, std::vector<GraphNode *> & result)
{
	GraphNode *n(GetNodeByKey(startKey));
	result.clear();
	if (n)
	{
		setAllUnvisited();
		inDepthsearchRek(startKey, n, result);
	}
}

void Graph::breadthSearchIter(int startKey, std::vector<GraphNode *> & result)
{
	std::queue<GraphNode *> node_q;
	GraphNode *n(GetNodeByKey(startKey));
	result.clear();
	if (n)
	{
		node_q.push(n);
		setAllUnvisited();
		while (!(node_q.empty()))
		{
			n = node_q.front();
			node_q.pop();
			if (!(n->_visited))
			{
				result.push_back(n);
				n->_visited = true;
				for (std::vector<GraphNode::edge>::iterator it(n->_edges.begin()), end(n->_edges.end()); it != end; ++it)
					node_q.push(it->node);
			}
		}
	}
}
//Or this
void Graph::depthSearchIter(int startKey, std::vector<GraphNode *> & result)
{
	std::stack<GraphNode *> node_s;
	GraphNode *n(GetNodeByKey(startKey));
	result.clear();
	if (n)
	{
		node_s.push(n);
		setAllUnvisited();
		while (!(node_s.empty()))
		{
			n = node_s.top();
			node_s.pop();
			if (!(n->_visited))
			{
				result.push_back(n);
				n->_visited = true;
				for (std::vector<GraphNode::edge>::iterator it(n->_edges.begin()), end(n->_edges.end()); it != end; ++it)
					node_s.push(it->node);
			}
		}
	}
}

void inBreadthSearchRek(GraphNode *node, std::queue<GraphNode *> & node_q)
{
	if (!(node->_visited))
	{
		node->_visited = true;
		for (std::vector<GraphNode::edge>::iterator it(node->_edges.begin()), end(node->_edges.end()); it != end; ++it)
		{
			node_q.push(it->node);
			inBreadthSearchRek(it->node, node_q);
		}
	}
}

void Graph::breadthSearchRek(int startKey, std::vector<GraphNode *> & result)
{
	GraphNode *n(GetNodeByKey(startKey));
	std::queue<GraphNode *> nodes_q;
	result.clear();
	if (n)
	{
		setAllUnvisited();
		inBreadthSearchRek(_nodes[0], nodes_q);
		while (!(nodes_q.empty()))
		{
			result.push_back(nodes_q.front());
			nodes_q.pop();
		}
	}
}

//This must be done by you
double Graph::prim(int startKey)
{
	double ret = 0.0;
	std::stack<GraphNode *> nodes_s;
	GraphNode *n(GetNodeByKey(startKey));
	GraphNode::edge *e;
	if (n)
	{
		setAllUnvisited();
		nodes_s.push(n);
		while (!(nodes_s.empty()))
		{
			n = nodes_s.top();
			nodes_s.pop();
			n->_visited = true;
			e = nullptr;
			for (std::vector<GraphNode::edge>::iterator it(n->_edges.begin()), end(n->_edges.end()); it != end; ++it)
			{
				if (!(it->node->_visited))
				{
					if (e)
					{
						if (e->value > it->value)
							e = &(*it);
					}
					else
						e = &(*it);
				}
			}
			if (e)
			{
				ret += e->value;
				nodes_s.push(e->node);
			}
		}
	}
	return ret;
}

void removeLoop(std::vector<GraphNode::edge> & edges)
{
	std::set<GraphNode *> nodes_set;
	for (std::vector<GraphNode::edge>::iterator it(edges.begin()), end(edges.end()); it != end; ++it)
	{
		if (nodes_set.find(it->node) != nodes_set.end())
		{
			edges.pop_back();
			break;
		}
		else
			nodes_set.insert(it->node);
	}
	nodes_set.clear();
}

double Graph::kruskal()
{
	double ret(0.0);
	std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, std::greater<GraphNode::edge> > edges_rpq;
	std::vector<GraphNode::edge> edges;
	for (std::vector<GraphNode *>::iterator it(_nodes.begin()), end(_nodes.end()); it != end; ++it)
	{
		for (std::vector<GraphNode::edge>::iterator e_it((*it)->_edges.begin()), e_end((*it)->_edges.end()); e_it != e_end; ++e_it)
			edges_rpq.push(*e_it);
	}
	setAllUnvisited();
	while (!(edges_rpq.empty()))
	{
		GraphNode::edge e(edges_rpq.top());
		edges_rpq.pop();
		edges.push_back(e);
		removeLoop(edges);
	}
	for (std::vector<GraphNode::edge>::iterator it(edges.begin()), end(edges.end()); it != end; ++it)
		ret += it->value;
	return ret;
}
