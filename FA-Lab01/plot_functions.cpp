/*
* @author Nita Eduard Marian
* @group 30423
* 
* program to plot some functions
*
*/

#include <conio.h>
#include <stdlib.h>
#include <math.h> 
#include "Profiler.h"

Profiler profiler("demo");

void linearFunction(int n) {
	Operation o = profiler.createOperation("linear", n);
	o.count(n);

}
void logFunction(int n) {
	Operation o = profiler.createOperation("log", n);
	o.count(100 * log(n));
}
void linearMultiplied(int n) {
	Operation o = profiler.createOperation("linear-multiplied", n);
	o.count(10 * n);
}
void quadraticHalved(int n) {
	Operation o = profiler.createOperation("quadratic-halved", n);
	o.count(0.5 * n * n);
}
void exponential(int n) {
	Operation o = profiler.createOperation("exponential", n);
	o.count(pow(2, n));
}

void factorial(int n) {
	int factorial = 1;
	for (int i = 1; i <= n; ++i)
	{
		factorial *= i;
	}
	Operation o = profiler.createOperation("factorial", n);
	o.count(2 * factorial);
}
int main() {

	int n;
	for (n = 100; n <= 10000; n += 100)
	{
		linearFunction(n);
		logFunction(n);
		linearMultiplied(n);
		quadraticHalved(n);
	}

	for (int n = 1; n <= 20; n++)
	{
		exponential(n);
	}

	for (int n = 1; n <= 10; n++)
	{
		factorial(n);
	}

	profiler.showReport();
	return 0;
}