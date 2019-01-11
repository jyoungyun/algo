#include <stdio.h>

int main(int argc, char *argv[])
{
	int q;
	long long l, r, s;
	int a, b;

	scanf("%d", &q);
	while (q--) {
		scanf("%lld %lld", &l, &r);
		s = r - l + 1;
		a = s >> 1;
		b = s % 2;
		if (l % 2)
			printf("%lld\n", 1 * a + -1 * r * b);
		else
			printf("%lld\n", -1 * a + 1 * r * b);
	}
  return 0;
}
