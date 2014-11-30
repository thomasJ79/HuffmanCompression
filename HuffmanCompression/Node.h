
/***************************************************************************************
*    Title: <CA1>
*    Author: <Thomas Jones X00105989 & Gary Curran X00095292  >
*    Date: <28 March 2014>
***************************************************************************************/
/***************************************************************************************
*    Title: <Huffman Coding>
*    Author: <Dream.In.Code> Knowles Y. Atchison, Jr. >
*    Date: <11 February 2011 - 02:20 PM>
*    Availability: <http://www.dreamincode.net/forums/topic/17915-huffman-coding/>
*
***************************************************************************************/
#ifndef NODE_H_
#define NODE_H_
#include<string>
#include<vector> 
using namespace std;

typedef int DATATYPE;

class Node
{

public:
	Node();
	Node(unsigned char c, int i);
	Node(Node* c0, Node *c1);

	~Node();

	bool operator<(const Node &a) const;

	int getWeight()							{ return weight; };
	char getValue()							{ return value; };
	Node* getChild0()						{ return child0; };
	Node* getChild1()						{ return child1; };

protected:
	string code;
	Node *child0, *child1;
	char value;
	int weight;

};
#endif

