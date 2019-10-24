/*
		@author Nita Eduard
		@group 30423

		Bottom-up build heap method:
			
			This method starts off from the assumption that we already have 2 heaps.
			We consider 1 single node as a very basic heap. So, half of nodes are already heaps.
			We start off with 2 heaps of dimension 1 and add their common parent node to build a heap of dimension 3.
			Half of all nodes are already heaps from the beginning.
			We apply heapify to the first non-leaf node (node in the tree with the largest index, having at least one child)
			We go to next indexed node and repeat.

			Average case: O(n)

		Top-down build heap method:

			This method works by inserting one element at the time into the heap, while the heap property is maintained at any moment.
			We do this by creating an element at the end of the heap.
			We assign the new value to that node. We compare its value with that of the node's parent.
			If the value of the parent is less than that of the child, then swap them.
			Repeat the comparison and swap process until the heap property holds.
			Then keep inserting wanted elements.

			Average case: O(n log n)

		Pros/Cons:
			
			At first glance, due to its speed, we would be inclined to think that
			the Bottom-up approach is better than its counterpart in every circumstance. Not quite.

			Although faster, the bottom-up approach has its short-comings when talking about variable in time input size.
			This method only works on inputs of fixed size, 
			while using the top-down approach allows us to add elements to our heart's content.

			Each implementation has its recommended applications, for example:
			The bottom-up approach can be used efficienty in heapsort, while
			the top-down approach, due to its variable dimension, allows us to implement priority queues in an effective manner.

		Worst case discussion:
			
			In the worst case, we can observe the following:
			
			The bottom-up approach hold its time complexity, that of O(n), making it useful even in the worst scenario.

			In the other case, we can see that the top-down method proves to be ineffective in this case,
			making it not a good choice for such input data.
*/


#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"
#include <math.h> 

#define MAX 10000

Profiler profiler("lab3");

int parent(int i) {
	return (i-1) / 2;
}

int	left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void maxHeapify(int A[], int i, int heapSize, int n)
{
	Operation ac = profiler.createOperation("acBottomUp", n);

	int largest;
	int leftChild = left(i);
	int rightChild = right(i);
	int aux;

	if (leftChild <= heapSize && A[leftChild] > A[i])
		largest = leftChild;
	else
		largest = i;
	ac.count(1);

	ac.count(1);
	if (rightChild <= heapSize && A[rightChild] > A[largest])
	{
		largest = rightChild;
	}

	if (largest != i)
	{
		aux = A[i];
		A[i] = A[largest];
		A[largest] = aux;
		ac.count(3);
		maxHeapify(A, largest, heapSize, n);
	}
}

void buildMaxHeap(int A[], int n, int heapSize) // bottom-up
{
	for (int i = n/ 2 - 1; i >= 0; i--)
		maxHeapify(A, i, heapSize, n);
}

void heapsort(int A[], int n)
{
	int heapSize = n - 1;
	int aux;
	buildMaxHeap(A, n, heapSize);
	for (int i = n - 1; i > 0; i--)
	{
		aux = A[0];
		A[0] = A[i];
		A[i] = aux;

		heapSize = heapSize--;
		maxHeapify(A, 0, heapSize, n);
	}
}

void MaxHeapIncreaseKey(int A[], int heapSize, int i, int key, int n)
{

	Operation ac = profiler.createOperation("acTopDown", n);

	int aux;
	A[i] = key;
	ac.count(1);

	while (i > 0 && A[parent(i)] < A[i])
	{

		aux = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = aux;
		i = parent(i);
		ac.count(4);
	}
}

void MaxHeapInsert(int A[], int key, int heapSize, int n)
{
	heapSize++;
	A[heapSize] = INT_MIN;
	MaxHeapIncreaseKey(A, heapSize, heapSize - 1, key, n);
}

void createDynamicHeap(int myEmptyHeap[], int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		MaxHeapInsert(myEmptyHeap, A[i], i, n);
	}
}

void generateWorst() {
	int initialArray[10001];
	int myCopiedArray[10001];
	int myEmptyHeap[10001];

	for (int i = 100; i <= 10001; i += 100)
	{
		FillRandomArray(initialArray, i, 10, 10000, false , 1);
		std::copy(initialArray, initialArray + i, myCopiedArray);
		buildMaxHeap(myCopiedArray, i, i);
		std::copy(initialArray, initialArray + i, myCopiedArray);
		createDynamicHeap(myEmptyHeap, myCopiedArray, i);
	}
}

void generateAverage() {
	int initialArray[10001];
	int myCopiedArray[10001];
	int myEmptyHeap[10001];

	for (int j = 0; j < 5; j++)
		for (int i = 100; i <= 10001; i += 100)
		{
			FillRandomArray(initialArray, i, 10, 10000);
			std::copy(initialArray, initialArray + i, myCopiedArray);
			buildMaxHeap(myCopiedArray, i, i);
			std::copy(initialArray, initialArray + i, myCopiedArray);
			createDynamicHeap(myEmptyHeap, myCopiedArray, i);
		}
}

int main() 
{

	int heap[100];
	int n = 10;
	int initialArray[10001];
	int myCopiedArray[10001];
	int myEmptyHeap[10001];
	
	printf("Test\n");
	printf("Random array generate:\n");
	FillRandomArray(heap, n, 10, 1000);

	for (int i = 0; i < n; i++)
		printf("%d ", heap[i]);

	std::copy(heap, heap + n, myCopiedArray);
	printf("\n");

	printf("\nBottom Up approach result:\n");
	buildMaxHeap(myCopiedArray, n, n);

	for (int i = 0; i < n; i++)
		printf("%d ", myCopiedArray[i]);

	printf("\n");
	std::copy(heap, heap + n, myCopiedArray);

	printf("\nTop Down approach result:\n");
	createDynamicHeap(myEmptyHeap, myCopiedArray, n);

	for (int i = 0; i < n; i++)
		printf("%d ", myEmptyHeap[i]);

	printf("\n");

	printf("\nHeapsort:\n");
	heapsort(heap, n);

	for (int i = 0; i < n; i++)
		printf("%d ", heap[i]);

	generateAverage();

	profiler.divideValues("acBottomUp", 5);
	profiler.divideValues("acTopDown", 5);

	profiler.createGroup("Operations BottomUp vs TopDown Average", "acBottomUp", "acTopDown");

	profiler.reset();

	generateWorst();

	profiler.createGroup("Operations BottomUp vs TopDown Worst", "acBottomUp", "acTopDown");

	profiler.showReport();
}