# Big-Natural-Number  (WORKING IN PROGRESS)
A tiny library to represent large numbers in C++.

## Example

```C
#include <iostream>
#include "natural.h"


int main()
{
#include <iostream>
#include "natural.h"

int main()
{
	const size_t bits = 1024;

	natural a(bits);

	// Set bit
	a[0] = 1;
	a[5] = 1;
	a.print_dec();

	// Loop with 1024 binary digits number
	for (natural i(bits); i < a; i++){
		i.print_dec();
	}

	natural b = a;
	if (a == b) printf("Equal\n");
	b += a;
	if (b > a) printf("Greater\n");
	if (a < b) printf("Less\n");
	if (b != a) printf("Not Equal\n");

	natural c(bits);
	c[3] = 1;
	a = c * b;
	c = b + a;

	// IT IS POSSIBLE TOO:
	// a = b % c;
	// a = b / c;
	// a = b - c;
	// a = b & c;
	// a = b | c;
	// a = ~b;

	if(c[0]) printf("Odd number\n");

	return 0;
}

```
