#include "Ringpuffer.h"
#include <iostream>

using namespace std;

const int Ringpuffer::puffer_size(6);

Ringpuffer::Ringpuffer() : Anker(nullptr)
{
	//
}

Ringpuffer::~Ringpuffer()
{
	clear();
}

void Ringpuffer::clear()
{
	for (RingNode *r(Anker), *p; r != nullptr;)
	{
		p = r;
		r = r->getNext();
		delete p;
	}
	Anker = nullptr;
}

RingNode * Ringpuffer::addNode(std::string description, const Tree & data)
{
	RingNode *ret(nullptr);
	if (puffer_size > 0)
	{
		ret = new RingNode(description, data, Anker);
		for (RingNode *rn(Anker), *p(nullptr); rn != nullptr; rn = rn->getNext())
		{
			rn->setAge(rn->getAge() + 1);
			if (rn->getAge() >= 6)
			{
				for (RingNode *t(rn), *p; t != nullptr;)
				{
					p = t;
					t = t->getNext();
					delete p;
				}
				if (p)
					p->detachLast();
				break;
			}
			p = rn;
		}
		Anker = ret;
	}
	return ret;
}

RingNode * Ringpuffer::search(std::string description)
{
	RingNode *ret(nullptr);
	for (RingNode *rn(Anker); rn != nullptr; rn = rn->getNext())
	{
		if (rn->getDescription() == description)
		{
			ret = rn;
			break;
		}
	}
	return ret;
}

void Ringpuffer::print()
{
	bool first(true);
	for (RingNode *rn(Anker); rn != nullptr; rn = rn->getNext())
	{
		if (first)
			first = false;
		else
			wcout << std::endl;
		rn->print();
		wcout << L"\n--------------------------";
	}
}

std::vector<RingNode *> & Ringpuffer::getAll(std::vector<RingNode *> & result)
{
	result.clear();
	for (RingNode *n(Anker); n != nullptr; n = n->getNext())
		result.push_back(n);
	return result;
}
