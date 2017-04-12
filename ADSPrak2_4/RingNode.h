#ifndef __RINGNODE_H__
#	define __RINGNODE_H__

#include <string>
#include "Tree.h"
class RingNode
{
private:
	RingNode();
	RingNode(const RingNode &);
	RingNode & operator = (const RingNode &);

	int OldAge;
	std::string Description;
	Tree *SymbolicData;
	RingNode *next;
public:
	RingNode(std::string description, const Tree & data, RingNode *_next = nullptr);
	~RingNode();

	int getAge();
	void setAge(int age);
	std::string getDescription();
	void setDescription(std::string description);
	Tree *getData();
	void setData(Tree *data);
	RingNode *getNext();
	void detachLast();
	void print();
};

#endif
