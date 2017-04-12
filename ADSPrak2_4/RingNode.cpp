#include "RingNode.h"
#include <iostream>

using namespace std;

RingNode::RingNode(std::string description, const Tree & data, RingNode *_next) : OldAge(0), Description(description), SymbolicData(new Tree(data)), next(_next)
{
	//
}

RingNode::~RingNode()
{
	delete SymbolicData;
	SymbolicData = nullptr;
}

int RingNode::getAge()
{
	return OldAge;
}

void RingNode::setAge(int age)
{
	if (age < 0)
		age = 0;
	OldAge = age;
}

std::string RingNode::getDescription()
{
	return Description;
}

void RingNode::setDescription(std::string description)
{
	Description = description;
}

Tree *RingNode::getData()
{
	return SymbolicData;
}

void RingNode::setData(Tree *data)
{
	SymbolicData = data;
}

RingNode * RingNode::getNext()
{
	return next;
}

void RingNode::detachLast()
{
	next = nullptr;
}

void RingNode::print()
{
	cout << "OldAge: " << OldAge << ", Descr: " << Description << ", Data:\n" << SymbolicData->toString();
}
