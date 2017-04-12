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
	RingNode *addNode(std::string description, const Tree & data);
	RingNode *search(std::string description);
	void print();
	std::vector<RingNode *> & getAll(std::vector<RingNode *> & result);
};

#endif
