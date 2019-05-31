/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#ifndef HASHNODE_HPP_
#define HASHNODE_HPP_

#include <iostream>
#include <string>
using namespace std;

class hashNode {

	friend class hashMap;
	string keyword;
	string *values;
	int valuesSize;
	int currSize;

public:

	hashNode();
	hashNode(string s);
	hashNode(string s, string v);
	~hashNode();
	void addValue(string v);
	void dblArray();
	string getRandValue();

};

#endif /* HASHNODE_HPP_ */
