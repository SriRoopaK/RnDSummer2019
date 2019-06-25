#include <stdio.h>

long power(long exponent) {
	long two_power = 2;
	for (long i = 0; i < exponent; i++) {
		two_power *= two_power;
	}
	return two_power;
}

long number_of_ways(long k, long steps) {
	if (steps == k) {
		return power(k - 1);
	}
	return 1 + number_of_ways(k, steps - 1);
}

/*int main(){
	long ways = number_of_ways(2, 5);
	printf("%ld", ways);
	getchar();
}*/