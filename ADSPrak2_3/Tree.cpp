#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Tree::deleteNode(TreeNode *& node)
{
	if (node)
	{
		deleteNode(node->getLeft());
		deleteNode(node->getRight());
		delete node;
		node = nullptr;
	}
}

std::vector<TreeNode*> & Tree::searchNodes(std::string & name, TreeNode *node, std::vector<TreeNode*> & result)
{
	if (node)
	{
		if (node->getName() == name)
			result.push_back(node);
		searchNodes(name, node->getLeft(), result);
		searchNodes(name, node->getRight(), result);
	}
	return result;
}

std::vector<TreeNode*> & Tree::getNodes(TreeNode * node, std::vector<TreeNode*>& result)
{
	if (node)
	{
		result.push_back(node);
		getNodes(node->getLeft(), result);
		getNodes(node->getRight(), result);
	}
	return result;
}

TreeNode * Tree::findNode(TreeNode * node, int node_pos_id)
{
	TreeNode *ret(nullptr);
	if (node)
	{
		if (node->getNodePosID() > node_pos_id)
			ret = findNode(node->getLeft(), node_pos_id);
		else if (node->getNodePosID() < node_pos_id)
			ret = findNode(node->getRight(), node_pos_id);
		else
			ret = node;
	}
	return ret;
}

TreeNode * Tree::removeNode(TreeNode * node, int node_pos_id, bool & result)
{
	TreeNode *n;
	if (node)
	{
		if (node->getNodePosID() > node_pos_id)
			node->getLeft() = removeNode(node->getLeft(), node_pos_id, result);
		else if (node->getNodePosID() < node_pos_id)
			node->getRight() = removeNode(node->getRight(), node_pos_id, result);
		else
		{
			if (node->getLeft())
			{
				if (node->getRight())
				{
					n = findMaximum(node->getLeft());
					(*node) = (*n);
					node->getLeft() = removeNode(node->getLeft(), n->getNodePosID(), result);
				}
				else
				{
					n = node->getLeft();
					delete node;
					node = n;
				}
			}
			else
			{
				if (node->getRight())
				{
					n = node->getRight();
					delete node;
					node = n;
				}
				else
				{
					delete node;
					node = nullptr;
				}
			}
			result = true;
		}
	}
	return node;
}

TreeNode * Tree::findMaximum(TreeNode * node)
{
	if (node)
	{
		if (node->getRight())
			node = node->getRight();
	}
	return node;
}

Tree::Tree() : anker(nullptr), l_node_id(-1)
{
	//
}

Tree::~Tree()
{
	clear();
}

TreeNode * Tree::addNode(std::string name, int alter, double einkommen, int plz)
{
	TreeNode *ret(new TreeNode(name, alter, einkommen, plz, ++l_node_id)), **pa(&anker);
	while ((*pa) != nullptr)
	{
		if ((*pa)->getNodePosID() > ret->getNodePosID())
			pa = &((*pa)->getLeft());
		else if ((*pa)->getNodePosID() < ret->getNodePosID())
			pa = &((*pa)->getRight());
		else
			break;
	}
	(*pa) = ret;
	return ret;
}

void Tree::clear()
{
	deleteNode(anker);
}

bool Tree::remove(int node_pos_id)
{
	bool ret(false);
	anker = removeNode(anker, node_pos_id, ret);
	return ret;
}

TreeNode * Tree::find(int node_pos_id)
{
	return findNode(anker, node_pos_id);
}

std::vector<TreeNode*> & Tree::search(std::string name, std::vector<TreeNode*> & result)
{
	result.clear();
	return searchNodes(name, anker, result);
}

std::vector<TreeNode*> & Tree::getAll(std::vector<TreeNode*> & result)
{
	result.clear();
	return getNodes(anker, result);
}

std::string Tree::toString()
{
	enum ETreeItem
	{
		ID,
		NAME,
		ALTER,
		EINKOMMEN,
		PLZ,
		POS,
		MAX_TREE_ITEMS
	};
	std::string ret;
	std::vector<TreeNode *> elements;
	struct Names
	{
		std::string names[MAX_TREE_ITEMS];
		Names(std::string node_id, std::string name, std::string alter, std::string einkommen, std::string plz, std::string node_pos_id)
		{
			names[ID] = node_id;
			names[NAME] = name;
			names[ALTER] = alter;
			names[EINKOMMEN] = einkommen;
			names[PLZ] = plz;
			names[POS] = node_pos_id;
		}
	};
	std::vector<Names> names;
	size_t sz[MAX_TREE_ITEMS];
	int i;
	bool first(true), first2;
	memset(sz, 0, sizeof(size_t) * MAX_TREE_ITEMS);
	getAll(elements);
	names.push_back(Names("ID", "Name", "Alter", "Einkommen", "PLZ", "Pos"));
	for (std::vector<TreeNode *>::iterator it(elements.begin()), end(elements.end()); it != end; ++it)
	{
		names.push_back(Names(std::to_string((*it)->getNodeID()), (*it)->getName(), std::to_string((*it)->getAlter()), std::to_string((*it)->getEinkommen()), std::to_string((*it)->getPLZ()), std::to_string((*it)->getNodePosID())));
	}
	for (std::vector<Names>::iterator it(names.begin()), end(names.end()); it != end; ++it)
	{
		for (i = 0; i < MAX_TREE_ITEMS; i++)
		{
			if (it->names[i].length() > sz[i])
				sz[i] = it->names[i].length();
		}
	}
	for (std::vector<Names>::iterator it(names.begin()), end(names.end()); it != end; ++it)
	{
		if (first)
			first = false;
		else
		{
			ret.push_back('\n');
			first2 = true;
			for (i = 0; i < MAX_TREE_ITEMS; i++)
			{
				if (first2)
					first2 = false;
				else
					ret += "-+-";
				ret.append(sz[i], '-');
			}
			ret.push_back('\n');
		}
		first2 = true;
		for (i = 0; i < MAX_TREE_ITEMS; i++)
		{
			if (first2)
				first2 = false;
			else
				ret += " | ";
			ret += it->names[i];
			ret.append(sz[i] - it->names[i].length(), ' ');
		}
	}
	return ret;
}

size_t Tree::parseCSV(std::istream & is)
{
	size_t ret(0UL);
	std::string l;
	while (std::getline(is, l))
	{
		std::vector<std::string> r;
		std::stringstream ss(l);
		std::string c;
		while (std::getline(ss, c, ','))
			r.push_back(c);
		if (!ss && c.empty())
			r.push_back(std::string());
		if (r.size() == 4)
			ret += (addNode(r[0], stoi(r[1]), stof(r[2]), stoi(r[3])) == nullptr) ? 0UL : 1UL;
	}
	return ret;
}
