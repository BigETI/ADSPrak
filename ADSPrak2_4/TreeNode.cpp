#include "TreeNode.h"
#include <iostream>

using namespace std;

void TreeNode::updateNodePosID()
{
	NodePosID = Alter + PLZ + static_cast<int>(Einkommen);
}

TreeNode::TreeNode(std::string name, int alter, double einkommen, int plz, int node_id) : Name(name), Alter(alter), Einkommen(einkommen), PLZ(plz), NodeID(node_id), links(nullptr), rechts(nullptr)
{
	updateNodePosID();
}

TreeNode::~TreeNode()
{
	//
}

TreeNode & TreeNode::operator=(const TreeNode & tree_node)
{
	Name = tree_node.Name;
	Alter = tree_node.Alter;
	Einkommen = tree_node.Einkommen;
	PLZ = tree_node.PLZ;
	NodeID = tree_node.NodeID;
	NodePosID = tree_node.NodePosID;
	return (*this);
}

int TreeNode::getNodePosID()
{
	return NodePosID;
}

int TreeNode::getNodeID()
{
	return NodeID;
}

std::string TreeNode::getName()
{
	return Name;
}

int TreeNode::getAlter()
{
	return Alter;
}

double TreeNode::getEinkommen()
{
	return Einkommen;
}

int TreeNode::getPLZ()
{
	return PLZ;
}

void TreeNode::printData()
{
	//
}

TreeNode *& TreeNode::getLeft()
{
	return links;
}

TreeNode *& TreeNode::getRight()
{
	return rechts;
}

std::string TreeNode::toString()
{
	return "NodeID: " + std::to_string(NodeID) + ", Name: " + Name + ", Alter: " + std::to_string(Alter) + ", Einkommen: " + std::to_string(Einkommen) + ", PLZ: " + std::to_string(PLZ) + ", PosID: " + std::to_string(NodePosID);
}
