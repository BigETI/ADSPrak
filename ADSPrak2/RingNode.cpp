#include "RingNode.h"
#include <iostream>

using namespace std;

RingNode::RingNode(std::string description, std::string data, RingNode *_next) : OldAge(0), Description(description), SymbolicData(data), next(_next)
{
	//
}

RingNode::~RingNode()
{
	//
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

std::string RingNode::getData()
{
	return SymbolicData;
}

void RingNode::setData(std::string data)
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
	cout << "OldAge: " << OldAge << ", Descr: " << Description << ", Data: " << SymbolicData;
}
