#ifndef __RINGPUFFER_H__
#	define __RINGPUFFER_H__

#include "RingNode.h"

class Ringpuffer
{
private:
	static const int puffer_size;
	RingNode *Anker;
public:
	Ringpuffer();
	~Ringpuffer();
	void clear();
	RingNode *addNode(std::string description, std::string data);
	RingNode *search(std::string data);
	void print();
};

#endif
