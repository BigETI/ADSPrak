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

RingNode * Ringpuffer::addNode(std::string description, std::string data)
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
			}
			p = rn;
		}
		Anker = ret;
	}
	
	return ret;
}

RingNode * Ringpuffer::search(std::string data)
{
	RingNode *ret(nullptr);
	for (RingNode *rn(Anker); rn != nullptr; rn = rn->getNext())
	{
		if (rn->getData() == data)
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
