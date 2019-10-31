#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"
#include <math.h> 

Profiler profiler("lab4");
int currentSize = 500;
FILE* fileIn;

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
	Operation oQ = profiler.createOperation("quicksortAC", currentSize);
	int aux, i, pivot;
	pivot = A[r];
	i = p - 1;

	for (int j = p; j < r; j++)
	{
		oQ.count();
		if (A[j] <= pivot)
		{
			i++;
			aux = A[i];
			A[i] = A[j];
			A[j] = aux;
			oQ.count(3);
		}
	}
	aux = A[i + 1];
	A[i + 1] = A[r];
	A[r] = aux;
	oQ.count(3);

	return i + 1;
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
	for(int j = 0; j < 4; j++)
		for (int i = 100; i <= 10000; i += 100) {
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
	for (int i = 500; i <= 10000; i += 500) {
		for (int j = 0; j < i; j++) {
			fscanf_s(fileIn, "%d ", &myBestArray[j]);
		}
		fscanf_s(fileIn, "%c", &buf);
		currentSize = i;
		quicksort(myBestArray, 0, i - 1);
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
	
	//generateBest();
	profiler.createGroup("Average QuickSort vs Heapsort", "heapsortAC", "quicksortAC");
	profiler.divideValues("heapsortAC", 5);
	profiler.divideValues("quicksortAC", 5);

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
