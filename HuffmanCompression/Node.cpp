
/***************************************************************************************
*    Title: <CA1>
*    Author: <Thomas Jones X00105989 & Gary Curran X00095292  >
*    Date: <28 March 2014>
***************************************************************************************/
#include "Node.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<std::string> vec;
Node::Node()
{
	value = NULL;
	weight = 0;
	child0 = child1 = NULL;
}

Node::~Node()
{
	if (child0 == NULL)
		delete child0;
	if (child1 == NULL)
		delete child1;
}

Node::Node(unsigned char c, int i)
{
	value = c;
	weight = i;
	child0 = child1 = NULL;

}

Node::Node(Node* c0, Node *c1) {
	value = NULL;
	weight = c0->weight + c1->weight; // Frequency of new node equals sum of frequency of left and right children
	child0 = c0;
	child1 = c1;

}

bool Node::operator<(const Node &a) const {
	return weight >a.weight;
}