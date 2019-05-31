/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#include "MakeSeuss.hpp"
#include "HashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

int main(){

	srand(time(NULL));
	makeSeuss("DrSeuss.txt", "NewSeuss.txt", false, false);

	return 0;
}


