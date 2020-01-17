/*
	@author Nita Eduard
	@group 30423

	Merge k ordered lists

	This algorithm takes as input k ordered list inputs where n is the total number of elements.
	The algorithms works by using a min heap to determine the smallest element out of all lists.
	This implementation uses a structure that saves the value of the element,
	as well as the index of the list from which it was taken form.

	At the start all the first elements of the lists are pushed into the min heap. 
	After each push we increment the pointer that tells us where the next element to be pushed from that list is located.
	Then, we pop the smallest element from the heap and add it to our output list.
	After the pop, we push into the heap the next element from the list that contained the popped element.

	The average case:
		O(nlogk)
		The average case of merging k lists with n elements can be easily determined if we already know that the push operation in a minheap is log k
		since this is repeated n times it amounts to nlog k operations

*/
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Profiler.h"
#include <list>
using namespace std;

int heapSize = 0;
static int arrayPointers[10001] = {};

char name[100];

typedef struct node {
	int value;
	int index;
} Node;

Profiler profiler("lab5");

int parent(int i) {
	return (i - 1) / 2;
}

int	left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void minHeapIncreaseKey(Node A[], int key, int arrIndex, int n)
{
	Operation ac = profiler.createOperation(name, n);
	int i = heapSize - 1;
	int aux, auxIndex;
	A[i].value = key;
	A[i].index = arrIndex;
	ac.count(1);

	while (i > 0 && A[parent(i)].value > A[i].value)
	{
		aux = A[i].value;
		A[i].value = A[parent(i)].value;
		A[parent(i)].value = aux;

		auxIndex = A[i].index;
		A[i].index = A[parent(i)].index;
		A[parent(i)].index = auxIndex;

		i = parent(i);
		ac.count(4);
	}
}

void push(Node A[], int key, int arrIndex, int n)
{
	heapSize++;
	A[heapSize].value = INT_MAX;
	A[heapSize].index = -1;

	minHeapIncreaseKey(A, key, arrIndex, n);
}

Node pop(Node A[], int n) {
	Operation ac = profiler.createOperation(name, n);

	if (heapSize > 0) {
		Node top;
		top.value = A[0].value;
		top.index = A[0].index;
		for (int i = 0; i < heapSize - 1; i++)
		{
			A[i].value = A[i + 1].value;
			A[i].index = A[i + 1].index;
		}
		ac.count(1);
		heapSize--;

		int i = heapSize - 1;
		while (i > 0 && A[parent(i)].value > A[i].value)
		{
			int aux, auxIndex;
			aux = A[i].value;
			A[i].value = A[parent(i)].value;
			A[parent(i)].value = aux;

			auxIndex = A[i].index;
			A[i].index = A[parent(i)].index;
			A[parent(i)].index = auxIndex;

			i = parent(i);
			ac.count(4);
		}


		return top;
	}
	return A[0];
}
	
void showlist(list <int> g)
{
	list <int> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << '\t' << *it;
	cout << '\n';
}

void printHeap(Node myHeap[]) {
	printf("\n");
	for (int i = 0; i < heapSize; i++) {
		printf("%d ", myHeap[i].value);
	}
	printf("\n");

}

void mergeArrays(vector<list<int>> input, Node myHeap[], int k, int n) {
	Operation ac = profiler.createOperation(name, n);
	list<int>::iterator it;
	list<int> output;
	for (int i = 0; i < k; i++) {
		it = input[i].begin();
		push(myHeap, *it, i, n);
		arrayPointers[i]++;
	} 
	
	for (int i = 0; i < n; i++) {
		
		Node aux = pop(myHeap, n);
		ac.count(1);
		output.push_back(aux.value);
		if (arrayPointers[aux.index] < input[aux.index].size()) {
			ac.count(1);
			it = next(input[aux.index].begin(), arrayPointers[aux.index]);
			push(myHeap, *it, aux.index, n);
			arrayPointers[aux.index]++;
		}
	}
	for (int i = 0; i < n; i++) {
		showlist(output);
	}
}

int main()
{
	vector<list<int>> vectorAll;
	int k = 3, n = 3;

	int myRandomValues[10001];
	Node myHeap[10001];

	for (int i = 0; i < k; i++)
	{	
		list<int> auxList;
		FillRandomArray(myRandomValues, n, 10, 10000, false, 1);
		for (int j = 0; j < n; j++) {
			auxList.push_back(myRandomValues[j]);
		}
		vectorAll.push_back(auxList);
	}

	for (int i = 0; i < k; i++) {
		showlist(vectorAll[i]);
	}

	mergeArrays(vectorAll, myHeap, k, k*n);
	vectorAll.clear();

	int k5 = 5, k10 = 10, k100 = 100;

	FILE* f;
	FILE* f5;
	FILE* f10;
	FILE* f100;

	fopen_s(&f, "output.txt", "r");
	fopen_s(&f5, "output5.txt", "r");
	fopen_s(&f10, "output10.txt", "r");
	fopen_s(&f100, "output100.txt", "r");

	/*sprintf_s(name, "%s", "k5operations");
	list<int> auxList;
	for (int i = 500; i <= 10000; i+=100) {
		for (int m = 0; m < k5; m++) {
			auxList.clear();
			int auxN;
			fscanf_s(f5, "%d%*c", &auxN);
			FillRandomArray(myRandomValues, auxN, 10, 10000, false, 1);
			for (int j = 0; j < auxN; j++) {
				auxList.push_back(myRandomValues[j]);
			}
			vectorAll.push_back(auxList);
		}
		mergeArrays(vectorAll, myHeap, k5, i);
		vectorAll.clear();
	}

	sprintf_s(name, "%s", "k10operations");
	for (int i = 500; i <= 10000; i+=100) {
		for (int m = 0; m < k10; m++) {
			int auxN;
			auxList.clear();
			fscanf_s(f10, "%d%*c", &auxN);
			FillRandomArray(myRandomValues, auxN, 10, 10000, false, 1);
			for (int j = 0; j < auxN; j++) {
				auxList.push_back(myRandomValues[j]);
			}
			vectorAll.push_back(auxList);
		}
		mergeArrays(vectorAll, myHeap, k10, i);
		vectorAll.clear();

	}

	sprintf_s(name, "%s", "k100operations");
	for (int i = 1000; i <= 10000; i+=100) {
		for (int m = 0; m < k100; m++) {
			int auxN;
			auxList.clear();
			fscanf_s(f100, "%d%*c", &auxN);
			FillRandomArray(myRandomValues, auxN, 10, 50000, false, 1);
			for (int j = 0; j < auxN; j++) {
				auxList.push_back(myRandomValues[j]);
			}
			vectorAll.push_back(auxList);
		}
		mergeArrays(vectorAll, myHeap, k100, i);
		vectorAll.clear();

	}*/

	//sprintf_s(name, "%s", "fixedN");
	//int N = 10000;
	//for (int i = 10; i <= 500; i += 10) {

	//	for (int j = 0; j < i; j++) {
	//		int auxN;
	//		auxList.clear();
	//		fscanf_s(f, "%d%*c", &auxN);
	//		FillRandomArray(myRandomValues, auxN, 10, 50000, false, 1);
	//		for (int j = 0; j < auxN; j++) {
	//			auxList.push_back(myRandomValues[j]);
	//		}
	//		vectorAll.push_back(auxList);
	//	}
	//	mergeArrays(vectorAll, myHeap, i, 10000);
	//	vectorAll.clear();

	//}

	//profiler.createGroup("fixed", "fixedN");
	profiler.createGroup("5,10,100", "k5operations", "k10operations", "k100operations");

	profiler.showReport();


}	
