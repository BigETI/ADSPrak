#ifndef __TREENODE_H__
#	define __TREENODE_H__

#include <string>
#include "TreeNode.h"

class TreeNode
{
private:
	TreeNode();
	TreeNode(const TreeNode &);

	int NodePosID;
	int NodeID;
	std::string Name;
	int Alter;
	double Einkommen;
	int PLZ;
	TreeNode *links;
	TreeNode *rechts;

	void updateNodePosID();
public:
	TreeNode(std::string name, int alter, double einkommen, int plz, int node_id);
	~TreeNode();
	TreeNode & operator = (const TreeNode &tree_node);
	int getNodePosID();
	int getNodeID();
	std::string getName();
	int getAlter();
	double getEinkommen();
	int getPLZ();
	void printData();
	TreeNode *& getLeft();
	TreeNode *& getRight();
	std::string toString();
};

#endif
