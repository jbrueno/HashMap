/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#ifndef MAKESEUSS_HPP_
#define MAKESEUSS_HPP_

#include "HashMap.hpp"
#include <iostream>
using namespace std;

class makeSeuss {

	hashMap *ht;
	string fn; // file name for input (“DrSeuss.txt”)
	string newfile; // name of output file

public:

	makeSeuss(string file, string newf, bool h1, bool c1);
	void readFile();
	void writeFile();

};

#endif /* MAKESEUSS_HPP_ */
