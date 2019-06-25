#include <stdio.h>
#include <unordered_map>
using namespace std;
long int fib(int n, std::unordered_map <int, int>& m)
{
	if (n < 0)
		return 0;
	if (n == 1 || n == 0)
		return 1;
	if (m[n - 1] && m[n - 2])
	{
		return m[n - 1] + m[n - 2];
	}
	else if (m[n - 1] && !m[n - 2])
	{
		return m[n - 1] + fib(n - 2, m);
	}
	else if (!m[n - 1] && m[n - 2])
	{
		return fib(n - 1, m) + m[n - 2];
	}
	else if (!m[n - 1] && !m[n - 2])
	{
		return fib(n - 1, m) + fib(n - 2, m);
	}
}
int main()
{
	unordered_map<int, int> ump;
	int n;
	printf("Enter: ");
	scanf("%d", &n);
	long int ans = fib(n, ump);
	printf("%ld", ans);
}

