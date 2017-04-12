#ifndef __TREE_H__
#	define __TREE_H__

#include "TreeNode.h"
#include <vector>

class Tree
{
private:
	TreeNode *anker;
	int l_node_id;

	void deleteNode(TreeNode *& node);
	std::vector<TreeNode *> & searchNodes(std::string & name, TreeNode *node, std::vector<TreeNode *> & result);
	std::vector<TreeNode *> & getNodes(TreeNode *node, std::vector<TreeNode *> & result);
	TreeNode *findNode(TreeNode *node, int node_pos_id);
	TreeNode *removeNode(TreeNode *node, int node_pos_id, bool & result);
	TreeNode *findMaximum(TreeNode *node);
public:
	Tree();
	~Tree();

	TreeNode *addNode(std::string name, int alter, double einkommen, int plz);
	void clear();
	bool remove(int node_pos_id);
	TreeNode *find(int node_pos_id);
	std::vector<TreeNode *> & search(std::string name, std::vector<TreeNode *> & result);
	std::vector<TreeNode *> & getAll(std::vector<TreeNode *> & result);
	std::string toString();
	size_t parseCSV(std::istream & is);
};

#endif
