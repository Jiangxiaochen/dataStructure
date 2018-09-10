#include "stack.h"
#include <stdio.h>

unsigned long fac_re(unsigned long n)
{
	if (n <= 1)
		return 1;
	return n * fac_re(n - 1);
}

unsigned long fac_it(unsigned long n)
{
	unsigned long res = 1;
	for (unsigned long i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}

unsigned long fac_st(unsigned long n)
{								/* 模拟压栈 */
	LinkStack_jxc < unsigned long >lsj;
	while (n > 1)
		lsj.push(n--);
	unsigned long res = 1;
	unsigned long tmp;
	while (lsj.pop(tmp))
		res *= tmp;
	return res;
}

int main(int argc, const char *argv[])
{
	if (atoi(argv[1]) == 1)
		printf("%lu\n", fac_re(atoi(argv[2])));
	else if (atoi(argv[1]) == 2)
		printf("%lu\n", fac_it(atoi(argv[2])));
	else if (atoi(argv[1]) == 3)
		printf("%lu\n", fac_st(atoi(argv[2])));
	return 0;
}
