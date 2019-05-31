/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#include "HashNode.hpp"
#include "HashMap.hpp"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	map = new hashNode*[mapSize];
	first = "is";
	numKeys = 0;
	mapSize = 5393;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;
	for (int i = 0; i < mapSize; i++) {
		map[i] = NULL;
	}
}

hashMap::~hashMap() {
	for (int i = 0; i < mapSize; i++) { // delete all of the hashNodes
		delete map[i];
	}
	delete[] map; // delete the array
}

void hashMap::addKeyValue(string k, string v) {

	if (numKeys / mapSize > 0.7) { // when the load factor is above 70%, rehash the map
		reHash();
	}
	int index = getIndex(k); // finds correct index for the key

	if (map[index] == NULL) { // if the index is empty, create a new hashNode there with the given key and value
		map[index] = new hashNode(k, v);
		numKeys++;
	} else { // if the key is already there, just add the value to the values array
		map[index]->addValue(v);
	}

}

int hashMap::getIndex(string k) { // finds the correct index of where a key should go in the map
	int index = calcHash(k);

	if (h1 == true && c1 == true) { // use the first hash and collision functions
		if (map[index] == NULL) { // if there is nothing in the node, return that index
			return index;
		} else if (map[index]->keyword != k) { // if the key in the node is not equal to the key we are inserting, use the collision handling method
			collisionct1++;
			index = collHash1(index, k);
			return index;
		} else { // the keyword is equal to the keyword already in the map, return that index
			return index;
		}
	} else if (h1 == false && c1 == false) { // same as above portion of code, just using calhash2 and collHash2 to find the index
		index = calcHash2(k);
		if (map[index] == NULL) {
			return index;
		} else if (map[index]->keyword != k) {
			collisionct1++;
			index = collHash2(index, k);
			return index;
		} else {
			return index;
		}
	} else if (h1 == true && c1 == false) {
		if (map[index] == NULL) {
			return index;
		} else if (map[index]->keyword != k) {
			collisionct1++;
			index = collHash2(index, k);
			return index;
		} else {
			return index;
		}
	} else {
		index = calcHash2(k);
		if (map[index] == NULL) {
			return index;
		} else if (map[index]->keyword != k) {
			collisionct1++;
			index = collHash1(index, k);
			return index;
		} else {
			return index;
		}
	}
}

int hashMap::calcHash(string k) { // turns a key to an index value
	int len = k.length();
	int h = 0;
	for (int i = len - 1; i > 0; i--) { // multiplies each previous result by 17 and adds the characters ascii value, then mods by the array size
		h = (h * 29 + (int) k[i]) % mapSize;
	}
	h = h % mapSize;

	return h;
}

int hashMap::calcHash2(string k) { // second hashing function to calculate index of key

	int len = k.length();
	int h = 0;
	for (int i = len - 1; i > 0; i--) { // adds all values of the characters
		h += (int) k[i];
	}
	h = h % mapSize; // mod by array size

	return h;
}

void hashMap::getClosestPrime() { // sets the mapSize to the next prime after it is doubled
	int nextPrime = (mapSize * 2) + 1;
	bool flag = false;

	while (!flag) { // while the next prime isnt found, continue looping
		nextPrime++;
		if (isPrime(nextPrime)) { // if the number is prime, exit the loop
			flag = true;
		}
	}
	mapSize = nextPrime;
}

bool hashMap::isPrime(int x) { // determines whether int x is a prime number or not, returns true if it is and false otherwise
	for (int i = 2; i < x / 2; i++) { // loop through all factors to see if the number is prime
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

void hashMap::reHash() { // doubles the map up to the next prime number, then rehashes the values

	int oldSize = mapSize;
	int newIndex;
	getClosestPrime(); // sets mapSize to double what it was then up to the next prime

	hashNode **tmp = new hashNode*[mapSize];

	for (int i = 0; i < mapSize; i++) {
		tmp[i] = NULL;
	}

	for (int i = 0; i < oldSize; i++) {
		if (map[i] == NULL) {
			continue;
		}
		cout << "LLLLLLLLLLL" << endl;
		newIndex = getIndex(map[i]->keyword);

		tmp[newIndex] = map[i];

		cout << tmp[newIndex]->keyword << endl;

	}
	delete [] map;
	map = tmp;
}

int hashMap::collHash1(int h, string k) { // linear probing, h is the original index that the key hashes to
	int index = h + 1;

	while (index < mapSize) { // before the index reaches the end of the array, see if the key can be added
		if (map[index] == NULL || map[index]->keyword == k) // if the node is null or has the same key, return that index
			return index;
		index++;
		collisionct2++; // add one to the collisionct2 due to a collision caused by this function
	}
	index = 0; // start checking from the beginning of the map if the end was reached

	while (index < h) { // before the index reaches its original intended value
		if (map[index] == NULL || map[index]->keyword == k) // before the index reaches its original intended value
			return index;
		index++;
		collisionct2++;
	}
}

int hashMap::collHash2(int h, string k) { // quadratic probing, find next index by adding 1^2, then 2^2, 3^3 to the index until an open spot was found
	int collIndex = h;
	int x = 1;

	while (collIndex < mapSize) { // while the collIndex isnt at the end of the array, look for a null spot in the array
		collIndex += pow(x, 2);
		if (map[collIndex] == NULL || map[collIndex]->keyword == k)
			return collIndex;
		x++;
		collisionct2++; // add one to the collisionct2 due to a collision caused by this function
	}

	collIndex = 0; // set to zero if the end of the array is reached and no index was found
	x = 1;

	while (collIndex < h) { // look for an open spot staring from the beginning of the array
		collIndex += pow(x, 2);
		if (map[collIndex] == NULL || map[collIndex]->keyword == k)
			return collIndex;
		x++;
		collisionct2++;
	}
}

int hashMap::findKey(string k) { // determines whether or not a key is already in the hashmap
	int index = getIndex(k); // find where the key should be if it were in the hashmap

	if (map[index] == NULL) { // if where the key should be is empty, it is not in the map so -1 is returned
		return -1;
	} else if (map[index]->keyword == k) { // the key is in the tree so return the index of where it is
		return index;
	}
	return -1;
}

void hashMap::printMap() { // prints each keyword and its values from the map
	for (int i = 0; i < mapSize; i++) { // print out the keyword
		cout << map[i]->keyword << " " << endl;
		for (int j = 0; j < map[j]->currSize; j++) { // print out all of the keywords values
			cout << map[i]->values[j] << " ";
		}
	}
}

