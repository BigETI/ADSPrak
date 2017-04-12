#ifndef __RINGNODE_H__
#	define __RINGNODE_H__

#include <string>
class RingNode
{
private:
	RingNode();
	RingNode(const RingNode &);
	RingNode & operator = (const RingNode &);

	int OldAge;
	std::string Description;
	std::string SymbolicData;
	RingNode *next;
public:
	RingNode(std::string description, std::string data, RingNode *_next = nullptr);
	~RingNode();

	int getAge();
	void setAge(int age);
	std::string getDescription();
	void setDescription(std::string description);
	std::string getData();
	void setData(std::string data);
	RingNode *getNext();
	void detachLast();
	void print();
};

#endif
