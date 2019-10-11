/* 
*
* @author Nita Eduard Marian
* @group 30423
*
* I/O functions
*
*/
#include <stdio.h>
#include <conio.h>
#define MAX_SIZE 100000
int main(){
	int n;
	FILE* fileOut;
	FILE* fileIn;
	fopen_s(&fileOut, "output.txt", "w");
	fopen_s(&fileIn, "input.txt", "r");
	int myArray[MAX_SIZE];
	
	printf("Enter number of elements: ");

	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("\na[%d] = ", i);
		scanf_s("%d", &myArray[i]);
	}

	printf("\nPrinting to screen...");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", myArray[i]);
	}

	printf("\nNow printing to file...");
	for (int i = 0; i < n; i++)
	{
		fprintf(fileOut, "%d ", myArray[i]);
	}

	printf("\nNow reading from file...");
	for(int i = 0; i < n; i++)
	{
		fscanf_s(fileIn, "%d", &myArray[i]);
	}

	printf("\nPrinting to screen numbers from file +1...");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", myArray[i] + 1);
	}

	return 0;
}