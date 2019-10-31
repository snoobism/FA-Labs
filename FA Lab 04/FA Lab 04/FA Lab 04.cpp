/*
	@author Nita Eduard
	@group 30423

	Heapsort

		Average case: O(n log n)
		Worst case: O(n log n)
		Best case: O(n log n)
		Aux space: O(1)

		Heap sort is a comparison based sorting technique based on Heap data structure. 
		It is similar to selection sort where we first find the maximum element
		and place the maximum element at the end. This implementation uses the heapify function.
		We repeat the same process for remaining element.

	Quicksort

		Average case: O(n log n)
		Worst case: O(n^2)
		Best case: O(n log n)
		Aux space: O(log n)

		Quicksort is a divide and conquer method for sorting.
		It works by partitioning an array into two parts, 
		then sorting the parts independently. Quicksort is popular because it is easy to implement and
		works well for a variety of different kinds of input data, while at the same time
		being substantially faster than any other sorting method in typical applications.

	Heapsort vs Quicksort

		While quicksort outspeeds heapsort almost every time, it would seem that when choosing one of them,
		our choice should obviously be quicksort. This is not the case, because quicksort has it's disadvantages. 
		
		Although not as fast as quicksort, heapsort has its advantage in the fact that
		it does not use auxiliary space proportional to the input size. 
		
		This said, in cases where working with large amounts of data we could run out of extra memory faster with quicksort than with heapsort.
		An example of this occuring can be seen in this implementation of the worst case for quicksort, where the time complexity in quadratic.
		The maximum input size was cut down to 5000 instead of 10000 due to the fact that it generated a stack overflow error.
		
		Speaking of worst case, another advantage of heapsort over quicksort its faster worst case runtime.
		This is important due to the fact that sometimes malicious input from an external source may mirror the quicksort worstcase.
		As we have seen in our graphs, quicksort worst case is devastating. As such, heapsort is prefered in such cases, due to its consistency.
		An example of this would be in the linux kernel, where the default sort function is heapsort:
		https://github.com/torvalds/linux/blob/e472c64aa4fa6150c6076fd36d101d667d71c30a/lib/sort.c#L194

	External resources:
	Best case generator for quicksort:
		https://algs4.cs.princeton.edu/23quicksort/QuickBest.java.html
		Note: original file was modified in order to fit the current type of input data
*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"
#include <math.h> 
#include <string>
#include <cstring>


Profiler profiler("lab4");
int currentSize = 500;
FILE* fileIn;

char quickCaseNameChar[100];


int parent(int i) {
	return (i - 1) / 2;
}

int	left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void maxHeapify(int A[], int i, int heapSize, int n)
{
	Operation oH = profiler.createOperation("heapsortAC", n);
	int largest;
	int leftChild = left(i);
	int rightChild = right(i);
	int aux;

	if (leftChild <= heapSize && A[leftChild] > A[i])
		largest = leftChild;
	else
		largest = i;
	oH.count(1);

	oH.count(1);
	if (rightChild <= heapSize && A[rightChild] > A[largest])
	{
		largest = rightChild;
	}

	if (largest != i)
	{
		aux = A[i];
		A[i] = A[largest];
		A[largest] = aux;
		oH.count(3);
		maxHeapify(A, largest, heapSize, n);
	}
}

void buildMaxHeap(int A[], int n, int heapSize) // bottom-up
{
	for (int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(A, i, heapSize, n);
}

void heapsort(int A[], int n)
{
	Operation oH = profiler.createOperation("heapsortAC", n);
	int heapSize = n - 1;
	int aux;
	buildMaxHeap(A, n, heapSize);
	for (int i = n - 1; i > 0; i--)
	{
		aux = A[0];
		A[0] = A[i];
		A[i] = aux;
		oH.count(3);

		heapSize = heapSize--;
		maxHeapify(A, 0, heapSize, n);
	}
}

int partition(int A[], int p, int r)
{
	Operation oQ = profiler.createOperation(quickCaseNameChar, currentSize);
	int i = p;
	int j = r + 1;
	int piv = A[p];
	int aux;

	while (true) {

		while (A[++i] < piv) {
			oQ.count();
			if (i == r)
				break;
		}

		while (piv < A[--j]) {
			oQ.count();
			if (j == p)
				break;
		}

		if (i >= j)
			break;
		
		aux = A[i];
		A[i] = A[j];
		A[j] = aux;
		oQ.count(3);
	}

	aux = A[p];
	A[p] = A[j];
	A[j] = aux;
	oQ.count(3);

	return j;
}

void quicksort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

int randomisedPartition(int A[], int p, int r)
{
	int i = rand() % (r - p) + p;
	int aux;
	aux = A[r];
	A[r] = A[i];
	A[i] = aux;

	return partition(A, p, r);
}

int randomisedSelect(int A[], int p, int r, int i)
{
	int q, k;
	if (p == r)
		return A[p];
	q = randomisedPartition(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	if (i < k)
		return randomisedSelect(A, p, q - 1, i);
	else
		return randomisedSelect(A, q + 1, r, i - k);
}
	
void generateAverage() {
	int myArray[10001];
	int myCopied[10001];
	sprintf(quickCaseNameChar, "%s", "avgCaseQuickSort");
	printf(quickCaseNameChar);

	for(int j = 0; j < 4; j++)
		for (int i = 500; i < 10000; i += 500) {
			currentSize = i;
			FillRandomArray(myArray, i, 10, 10000);
			std::copy(myArray, myArray + i, myCopied);
			quicksort(myCopied, 0, i - 1);
			std::copy(myArray, myArray + i, myCopied);
			heapsort(myCopied, i);
		}
}

void generateBest() {
	int myBestArray[10001];
	char buf;
	sprintf(quickCaseNameChar, "%s", "bstCaseQuickSort");
	printf(quickCaseNameChar);

	for (int i = 500; i < 10000; i += 500) {
		for (int j = 0; j < i; j++) {
			if( j!=i-1)
				fscanf_s(fileIn, "%d ", &myBestArray[j]);
			else
				fscanf_s(fileIn, "%d \n", &myBestArray[j]);
		}

		currentSize = i;
		quicksort(myBestArray, 0, i - 1);
	}
}

void generateWorst() {
	int myWorstArray[10001];
	sprintf(quickCaseNameChar, "%s", "wstCaseQuickSort");
	printf(quickCaseNameChar);

	for (int i = 500; i <= 5000; i += 500) {
		FillRandomArray(myWorstArray, i, 10, 10000, false, 2);
		currentSize = i;
		quicksort(myWorstArray, 0, i - 1);
	}
}

int main()
{
	fopen_s(&fileIn, "inputC.txt", "r");

	int myRandomArray[10001];
	int n = 10;
	
	FillRandomArray(myRandomArray, n, 10, 1000);

	for (int i = 0; i < n; i++)
		printf("%d ", myRandomArray[i]);
	
	printf("\n");

	printf("#%d#\n", randomisedSelect(myRandomArray, 0, n - 1, 1));
	
	quicksort(myRandomArray, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf("%d ", myRandomArray[i]);

	generateAverage();
	generateBest();
	generateWorst();
	profiler.divideValues("heapsortAC", 5);
	profiler.divideValues("avgCaseQuickSort", 5);

	profiler.createGroup("Worst case QuickSort showcase", "heapsortAC", "avgCaseQuickSort","wstCaseQuickSort","bstCaseQuickSort");
	profiler.showReport();

	profiler.createGroup("QuickSort vs Heapsort", "heapsortAC", "avgCaseQuickSort", "bstCaseQuickSort");
	profiler.showReport();

	// //code for generating inputJava.txt file
	/*FILE* fileOut;
	fopen_s(&fileOut, "inputJava.txt", "w");
	
	for (int i = 500; i <= 10000; i += 500) {
		int randomArray[10001];
		FillRandomArray(randomArray, i, 10, 100000, false, 1);
		for (int j = 0; j < i; j++) {
			fprintf_s(fileOut, "%d", randomArray[j]);
			if (j != i - 1) {
				fprintf_s(fileOut, " ");
			}
		}
		fprintf_s(fileOut, "\n");
	}*/



	srand(time(NULL));
}
