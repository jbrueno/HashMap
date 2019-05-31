/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#include "HashNode.hpp"
#include <string>
#include <iostream>
using namespace std;

hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
}

hashNode::hashNode(string s) {
	keyword = s;
	valuesSize = 50;
	currSize = 0;
	values = new string[valuesSize];
	for(int i = 0; i < valuesSize; i++){
		values[i] = "";
	}
}

hashNode::hashNode(string s, string v) {
	keyword = s;
	valuesSize = 50;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
	for(int i = 1; i < valuesSize; i++){
		values[i] = "";
	}
}

void hashNode::addValue(string v) { // adds a value to the values array
	if (currSize >= valuesSize) {
		dblArray();
	}
	values[currSize] = v;
	currSize++;
}

hashNode::~hashNode(){
	delete [] values;
}

void hashNode::dblArray() { // doubles the array size

	string *tmp;
	tmp = new string[2 * valuesSize];
	for (int i = 0; i < currSize; i++) { // copy over values
		tmp[i] = values[i];
	}
	valuesSize *= 2;
	delete[] values;
	values = tmp;

}

string hashNode::getRandValue() { // returns random value in the values array where there is a value and not null
	if(values[0] == ""){
		return "";
	} else {
		int randomInt = rand()%currSize;
		return values[randomInt];
	}
}

