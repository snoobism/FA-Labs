/*
	@author Nita Eduard
	@group 30423

	Hash tables are data structures used for efficient storage and manipulation of data, inserting each element according to what it contains.
	When searching for an element, instead of searching for i to array size, we calculate the element's index based on a hash function and search there.
	If it is not there, we probe the next position and so on.

	This hash function uses quadratic probing, which access, as the name suggests, the next position at (ax^2 + bx + c) places away from the current one.
	As a % factor, we use a prime number, since it offers a large pool of remainders.

	By analysing the table generated by this code, we can see that the average effort in finding items 
	increases proportionally to the load factor, which makes total sense.
	This means that when the table is loaded with more items, there is less empty space, thus it is harder to find the desired item. (more items to be checked)

*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"
using namespace std;
#define HASH_SIZE 10007

Profiler profiler("lab");

typedef struct person {
	int id;
	char name[30];
}Entry;

Entry myHashTable[10007];
int effort = 0;
int m = 3000;


int hashFunction(Entry table[], Entry k, int i) {
	return (k.id + 5 * i + 7 * i * i) % HASH_SIZE;
}

int hashInsert(Entry table[], Entry k) {
	int i = 0;
	do {
		int j = hashFunction(table, k, i);
		if (table[j].id == -1) {
			table[j] = k;
			return j;
		}
		else {
			i++;
		}
	} while (i != HASH_SIZE);
}

int hashSearch(Entry table[], Entry k) {
	int i = 0, j;
	do {
		j = hashFunction(table, k, i);
		effort++;
		if (table[j].id == k.id && strcmp(table[j].name, k.name) == 0) {
			return j;
		}
		else if(table[j].id == -1){
			return 0;
		}
		i = i + 1;
	} while (i != HASH_SIZE);
	return -1; // aka null for poor people
}

void genRandom(char* s, const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

void initialiseHashTable(Entry table[]) {
	for (int i = 0; i < HASH_SIZE; i++) {
		table[i].id = -1;
		strcpy_s(table[i].name, "-1");
	}
}

void printHashTable(Entry table[]) {
	for (int i = 0; i < HASH_SIZE; i++) {
		cout << table[i].id << " " << table[i].name << endl;
	}
}


int main() {
	int myRandomArray[10007];
	float alpha[5] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	int n[5] = { alpha[0] * HASH_SIZE, alpha[1] * HASH_SIZE, alpha[2] * HASH_SIZE, alpha[3] * HASH_SIZE, alpha[4] * HASH_SIZE };

	int myData[10007];
	int myRandomFound[3000];
	int myRandomNotFound[3000];

	printf("Load    \tavgF    \tmaxF\tavgNF    \tmaxNF\n");
	for (int i = 0; i < 5; i++) {
		float avgEffortFound = 0;
		float avgEffortNotFound = 0;
		int avgMaxEffortFound = -1;
		int avgMaxEffortNotFound = -1;

		for (int k = 0; k < 5; k++) {
			int found = 0;
			int notFound = 0;
			double effortFound = 0;
			double effortNotFound = 0;
			int maxEffortFound = -1;
			int maxEffortNotFound = -1;
			initialiseHashTable(myHashTable);
			FillRandomArray(myData, n[i], 1, 15000, true, 0);
			FillRandomArray(myRandomFound, 1500, 0, n[i], true, 0); // found
			FillRandomArray(myRandomNotFound, 1500, 15000, 30000, true, 0); // not found

			for (int j = 0; j < n[i]; j++) {
				Entry auxEntry;
				auxEntry.id = myData[j];
				sprintf_s(auxEntry.name, "%d", myData[j]);
				hashInsert(myHashTable, auxEntry);
			}


			for (int j = 0; j < 1500; j++) {
				effort = 0;
				Entry auxEntry;
				auxEntry.id = myData[myRandomFound[j]];
				sprintf_s(auxEntry.name, "%d", myData[myRandomFound[j]]);
				if (hashSearch(myHashTable, auxEntry) != 0) {
					effortFound += effort;
					if (effort > maxEffortFound) {
						maxEffortFound = effort;
					}
					found++;
				}

			}

			for (int j = 0; j < 1500; j++) {
				effort = 0;
				Entry auxEntry;
				auxEntry.id = myRandomNotFound[j];
				sprintf_s(auxEntry.name, "%d", myRandomNotFound[j]);
				if (hashSearch(myHashTable, auxEntry) == 0) {
					effortNotFound += effort;
					if (effort > maxEffortNotFound) {
						maxEffortNotFound = effort;
					}
					notFound++;
				}

			}
			effortFound /= found;
			effortNotFound /= notFound;

			avgEffortFound += effortFound;
			avgEffortNotFound += effortNotFound;

			avgMaxEffortFound += maxEffortFound;
			avgMaxEffortNotFound += maxEffortNotFound;

			//printf("%d, %d\n", found, notFound);
		}
		printf("%f\t%f\t%d\t%f\t%d\n", alpha[i], (avgEffortFound) / 5, avgMaxEffortFound / 5, (avgEffortNotFound) / 5, avgMaxEffortNotFound/5);

	}
}