/*
* @author Nita Eduard Marian
* @group 30423
*
*	BubbleSort - The bubble sort gets its name 
*	because elements tend to move up into the correct order
*	like bubbles rising to the surface.	
*	This algorithm works by comparing each element with the following others
*	and if the selected element is greater
*	than the following one, it gets switched. 
*	Altough easy to understand, this algorithm is highly inefficient to due
*	it's high number of swaps between elements.
*	Besides using it to understand the basics of sorting, it is not advised to use this algorithm.
*		Worst case: O(n^2)
*		Best case: O(n)
*		Average case: O(n^2)
*		Stable
*
*	InsertionSort - The insertion sort works by starting with a sorted array, that is a subset of the whole array 
*	(in the beginning it contains only the first element of the whole array)
*	then it selects the following element and inserts it into the appropriate place
*	in the sorted array. This continues with the following elements until there
*	are no more elements that are not part of the sorted array
*		Worst case: O(n^2)
*		Best case: O(n)
*		Average case: O(n^2)
*		Stable
*
*	SelectionSort - The selection sort works by iterating through the whole array
*	and swapping the current element with the smallest element that 
*	does not belong to the sorted part of the array. This continues until
*	there are no more unsorted elements.
*		Worst case: O(n^2)
*		Best case: O(n^2)
*		Average case: O(n^2)
*		Unstable(ex:
*			4 2 3 4 1, 
*		1 is swapped with 4, thus reversing the order of the first 4 and second 4
*		)
*	
*	Comparing the algorithms:
*		By analysing the best cases of each algorithm we can observe the following:
*		Although Bubble Sort has the lowest count of comparisons and assignments, 
*		in our current state that is not so useful because... the array is already sorted, 
*		a case which is quite rare and has no practical use in the real world. 
*		After bubble sort, the lowest count of comparisons and assignments belongs to 
*		insertion sort, which is roughly 3x times that of bubble sort. Behind these two 
*		we have selection sort which has roughly (n^2)/2 assignments and comparisions, 
*		which is not a great number, but there is no need to panic since the best case is rare
*
*		By analysing the worst case of each algorithm we can observe the following:
*		This time, bubble sort takes the lead in most comparisons and assignments, 
*		at around 2*(n^2). After that, both insertion sort and selection sort have 
*		almost the same number of assignments and comparisons at (n^2)/2
*
*		By analysing the average case of each algorithm we can observe the following:
*		First of all, bubble sort is performing, by far, the worst. It has over n^2 assignments + comparisons, 
*		while, selection sort still has (n^2)/2 assignments and comperisons. The best of
*		all three is easily insertion sort with roughly (n^2)/4.
*
*		TLDR: use insertion sort.
*	
*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"
#include <math.h> 


Profiler profiler("lab2");

void bubbleSort(int myArray[], int n)
{
	Operation assign = profiler.createOperation("assignBubble", n);
	Operation compare = profiler.createOperation("compareBubble", n);
	Operation assignPlusCompare = profiler.createOperation("acBubble", n);

	int aux;
	int swapped = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			compare.count(1);
			assignPlusCompare.count(1);
			if (myArray[j] > myArray[j + 1])
			{
				aux = myArray[j];
				myArray[j] = myArray[j + 1];
				myArray[j + 1] = aux;
				swapped = 1;
				assign.count(3);
				assignPlusCompare.count(3);

			}
		}
		if (swapped == 0)
		{
			break;
		}
	}
}

void insertionSort(int myArray[], int n)
{
	Operation assign = profiler.createOperation("assignInsertion", n);
	Operation compare = profiler.createOperation("compareInsertion", n);
	Operation assignPlusCompare = profiler.createOperation("acInsertion", n);
	
	int key, j;
	for (int i = 1; i < n - 1; i++)
	{
		key = myArray[i];
		assign.count(1);
		assignPlusCompare.count(2);
		j = i - 1;
		compare.count(1);

		while (j >= 0 && myArray[j] > key)
		{
			myArray[j + 1] = myArray[j];
			assign.count(1);
			assignPlusCompare.count(1);
			j = j - 1;
		}
		myArray[j + 1] = key;
		assign.count(1);
		assignPlusCompare.count(1);
	}
}

void selectionSort(int myArray[], int n)
{
	Operation assign = profiler.createOperation("assignSelection", n);
	Operation compare = profiler.createOperation("compareSelection", n);
	Operation assignPlusCompare = profiler.createOperation("acSelection", n);

	int aux, minIndex;
	for (int i = 0; i < n - 1; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			compare.count(1);
			assignPlusCompare.count(1);
			if (myArray[j] < myArray[minIndex])
			{
				minIndex = j;
			}
		}


		aux = myArray[minIndex];
		myArray[minIndex] = myArray[i];
		myArray[i] = aux;
		assign.count(3);
		assignPlusCompare.count(3);
	}
}

void quadratic(int n) {
	Operation o = profiler.createOperation("n*n", n);
	o.count(n * n);
}

void generateBestCase(int myRandomArray[]) {
	int myCopiedArray[10001];

	for (int i = 500; i <= 5000; i += 500)
	{
		FillRandomArray(myRandomArray, i, 10, 10000, false, 1);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		bubbleSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		insertionSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		selectionSort(myCopiedArray, i);

	}
}

void generateWorstCase(int myRandomArray[]) {
	int myCopiedArray[10001];

	for (int i = 500; i <= 5000; i += 500)
	{
		FillRandomArray(myRandomArray, i, 10, 10000, false, 2);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		bubbleSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		insertionSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		selectionSort(myCopiedArray, i);

	}
}

void generateAverageCase(int myRandomArray[]) {
	int myCopiedArray[10001];

	for (int i = 500; i <= 5000; i += 500)
	{
		FillRandomArray(myRandomArray, i, 10, 10000);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		bubbleSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		insertionSort(myCopiedArray, i);
		std::copy(myRandomArray, myRandomArray + i, myCopiedArray);
		selectionSort(myCopiedArray, i);

	}
}


int main()
{
	const int MAXX = 10001;
	int myRandomArray[MAXX];
	int myCopiedArray[MAXX];

	generateBestCase(myRandomArray);
	profiler.createGroup("BestCase Assignments plus Comparison Insertion vs Selection vs Bubble", "acInsertion", "acBubble", "acSelection");
	profiler.createGroup("BestCase Comparisons Insertion vs Selection vs Bubble", "compareInsertion", "compareBubble", "compareSelection");
	profiler.createGroup("BestCase Assignments Insertion vs Selection vs Bubble", "assignInsertion", "assignBubble", "assignSelection");

	profiler.reset();

	generateWorstCase(myRandomArray);
	profiler.createGroup("WorstCase Assignments plus Comparison Insertion vs Selection vs Bubble", "acInsertion", "acBubble", "acSelection");
	profiler.createGroup("WorstCase Comparisons Insertion vs Selection vs Bubble", "compareInsertion", "compareBubble", "compareSelection");
	profiler.createGroup("WorstCase Assignments Insertion vs Selection vs Bubble", "assignInsertion", "assignBubble", "assignSelection");

	profiler.reset();

	for(int j = 0; j < 5; j++)
		generateAverageCase(myRandomArray);
	profiler.divideValues("acInsertion", 5);
	profiler.divideValues("acBubble", 5);
	profiler.divideValues("acSelection", 5);
	profiler.divideValues("assignInsertion", 5);
	profiler.divideValues("assignBubble", 5);
	profiler.divideValues("assignSelection", 5);
	profiler.divideValues("compareInsertion", 5);
	profiler.divideValues("compareBubble", 5);
	profiler.divideValues("compareSelection", 5);


	profiler.createGroup("AverageCase Assignments plus Comparison Insertion vs Selection vs Bubble", "acInsertion", "acBubble", "acSelection");
	profiler.createGroup("AverageCase Comparisons Insertion vs Selection vs Bubble", "compareInsertion", "compareBubble", "compareSelection");
	profiler.createGroup("AverageCase Assignments Insertion vs Selection vs Bubble", "assignInsertion", "assignBubble", "assignSelection");

	profiler.showReport();
}


