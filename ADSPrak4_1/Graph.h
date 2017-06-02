#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"
#include <deque>
#include <map>
#include <queue>
#include <iostream>

class Graph
{
public:
    Graph();
    ~Graph();

    GraphNode* GetNodeByKey(int key);
    void setAllUnvisited();
    bool checkVisited();
    bool init(std::string path);
    bool print();
	void clear();

    //Implement this:
	bool depthSearchRek(int startKey, std::vector<GraphNode *> & result);
	bool breadthSearchIter(int startKey, std::vector<GraphNode *> & result);
    //Or this
	bool depthSearchIter(int startKey, std::vector<GraphNode *> & result);
	bool breadthSearchRek(int startKey, std::vector<GraphNode *> & result);

    //This must be done by you
    double prim(int startKey);
    double kruskal();

    //They might be helpful
    int _anzKnoten;
    //bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
