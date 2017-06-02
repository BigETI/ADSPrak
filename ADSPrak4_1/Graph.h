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
	void depthSearchRek(int startKey, std::vector<GraphNode *> & result);
	void breadthSearchIter(int startKey, std::vector<GraphNode *> & result);
    //Or this
    void depthSearchIter(int startKey, std::vector<GraphNode *> & result);
	void breadthSearchRek(int startKey, std::vector<GraphNode *> & result);

    //This must be done by you
    double prim(int startKey);
    double kruskal();

    //They might be helpful
    int _anzKnoten;
    //bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
