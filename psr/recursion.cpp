#include <stdio.h>

long long factorial(int n)
{
  if (n == 1) return 1;
  return n * factorial(n - 1);
}

int main()
{
  int T;
  int N;

  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    scanf("%d", &N);

    printf("#%d %d! = %lld\n", t, N, factorial(N));
  }

  return 0;
}
