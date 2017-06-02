#include "GraphNode.h"

GraphNode::GraphNode(int key)
{
    _key = key;
    _visited = false;
    _distance = 0.;
    //_prev = nullptr;
    _edges.clear();
}

bool GraphNode::hasNeighbor(int neighborKey)
{
    for (int i = 0; i < _edges.size(); i++) {
        if(_edges[i].node->_key == neighborKey){
            return true;
        }
    }
    return false;
}

GraphNode::edge GraphNode::getEdgeByNeigborkey(int key)
{
    for(int i = 0; i != _edges.size(); i++)
    {
        edge currentEdge = _edges[i];
        if(currentEdge.node->_key == key)
        {
            return currentEdge;
        }
    }

    return GraphNode::edge(nullptr, 0.0);
}
