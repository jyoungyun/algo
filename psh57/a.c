#include <stdio.h>

#ifdef ONLINE_JUDGE
#define LL    "%I64d"
#else
#define LL    "%lld"
#endif

int main(int argc, char *argv[])
{
  int t;
  int a, b, k, s;
  scanf("%d", &t);

  while (t--) {
    scanf("%d %d %d", &a, &b, &k);
    s = a - b;
    printf(LL"\n", (long long)s * (k/2) + a * (k%2));
  }

  return 0;
}
