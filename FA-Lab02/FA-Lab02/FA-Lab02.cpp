/*
*
* @author Nita Eduard Marian
* @group 30423
*
*	Program plots the resulting bubblesort comparisons/assignments 
*	for an input size in the range of [100, 10000] with an increment of 500
*	as well as plotting n*n, which is supposed to be worst case
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
	Operation assign = profiler.createOperation("assign", n);
	Operation compare = profiler.createOperation("compare", n);
	int aux;
	int swapped = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i + 1; j++)
		{
			if (myArray[j] > myArray[j + 1])
			{
				compare.count(1);
				aux = myArray[j];
				myArray[j] = myArray[j + 1];
				myArray[j + 1] = aux;
				swapped = 1;
				assign.count(3);

			}
		}
		if (swapped == 0)
		{
			break;
		}
	}
}
void quadratic(int n) {
	Operation o = profiler.createOperation("n*n", n);
	o.count(n * n);
}

int main()
{
	const int MAXX = 10001;
	int n = 10;
	int myRandomArray[MAXX];

	//printf("Please enter the input size: ");
	//scanf_s("%d", &n);

	
	/*
	FillRandomArray(myRandomArray, MAXX, 10, 10000);
	printf("Array before sorting:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", myRandomArray[i]);
	}
	bubbleSort(myRandomArray, n, assign, compare);
	printf("\nArray after sorting:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", myRandomArray[i]);
	}
	*/

	for (int i = 100; i <= 10000; i += 500)
	{
		FillRandomArray(myRandomArray, i, 10, 100);
		quadratic(i);
		bubbleSort(myRandomArray, i);
	}
	
	profiler.createGroup("Comp vs Asign vs n*n", "compare", "assign","n*n");
	profiler.showReport();
}


