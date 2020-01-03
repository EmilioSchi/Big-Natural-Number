# Big-Natural-Number  (WORKING IN PROGRESS)
A tiny library to represent large numbers in C++.

## Example

```C
#include <iostream>
#include "natural.h"


int main()
{
	const size_t bits = 256;

	natural a(bits);
	natural b(bits);

	// Set bit
	a[5] = 1;
	b[10] = 1;

	// Operation
	b = a * b;

	a[23] = 1;
	b += a;


	a = b;
	natural c = a;
	//c = b / a;

	a.print_bin();
	b.print_bin();
	c.print_bin();

	//(a - b).print_bin();

	if(a == c) printf("True \n");

	return 0;
}

```
