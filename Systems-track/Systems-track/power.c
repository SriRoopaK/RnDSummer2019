#include <stdio.h>
#include <stdlib.h>
long int power(int a, int n)
{
	long int t = power(a, n / 2);
	long int m = power(10, 9) + 7;
	if (n == 0)
	{
		if (n % 2 == 0)
			return (t % m) * (t % m);
		return (t % m) * (t % m) * (a % m);
	}
	
}