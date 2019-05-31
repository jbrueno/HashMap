/*
 * Joseph Brueno
 * April 30, 2019
 *
 */

#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

#include "HashNode.hpp"

class hashMap {
	friend class makeSeuss;
	hashNode **map;
	string first;
	int numKeys;
	int mapSize;
	bool h1;
	bool c1;
	int collisionct1;
	int collisionct2;
public:
	hashMap(bool hash1, bool coll1);
	~hashMap();
	void addKeyValue(string k, string v);
	int getIndex(string k);
	int calcHash(string k);
	int calcHash2(string k);
	void getClosestPrime();
	bool isPrime(int x); // getClosestPrime helper function
	void reHash();
	int collHash1(int h, string k);
	int collHash2(int h, string k);
	int findKey(string k);
	void printMap();
};

#endif /* HASHMAP_HPP_ */
