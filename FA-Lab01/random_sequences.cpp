/*
*
* @author Nita Eduard Marian
* @group 30423
*
* randomLowHighArray is a function that prints 
*	an array of length n which contains random integers 
*	between a LOW and HIGH boundary
*
* randomSortedArray is a function that prints
*	an array of length n which contains sorted random integers
*	This is done by repeatedly generating a random number between LOW(which is 0 at first)
*	and INT_MAX(HIGH) and then setting that new number as the LOW boundary
*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       /* time */

void randomLowHighArray(int n) {
	int low, high;

	printf("Enter LOW value:");
	scanf_s("%d", &low);
	printf("\nEnter HIGH value: ");
	scanf_s("%d", &high);

	printf("\nRandom array of lenth %d between %d and %d:\n", n, low, high);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", rand() % (high + 1 - low) + low);
	}
}

void randomSortedArray(int n) {
	int sortedLow = 0;
	int sortedMax = INT_MAX;
	int sortedArray[100000];

	printf("\n Random ordered array of length %d:\n", n);
	for (int i = 0; i < n; i++)
	{
		sortedArray[i] = rand() % (sortedMax - sortedLow) + sortedLow;
		sortedLow = sortedArray[i];
		printf("%d ", sortedArray[i]);
	}

	printf("\nDone.");
}

int main(){

	int n;
	srand(time(NULL));

	printf("\nInput array size:");
	scanf_s("%d", &n);

	randomLowHighArray(n);

	randomSortedArray(n);

	_getch();

}