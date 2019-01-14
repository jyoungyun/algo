#include <stdio.h>

#define RED   (2)
#define GRN   (5)
#define BLU   (8)

int main(int argc, char *argv[])
{
  int n, k;

  scanf("%ld %ld", &n, &k);

  long long sum = 0;

  sum += ((RED*n) / k);
  sum += ((RED*n) % k == 0 ? 0 : 1);
  sum += ((GRN*n) / k);
  sum += ((GRN*n) % k == 0 ? 0 : 1);
  sum += ((BLU*n) / k);
  sum += ((BLU*n) % k == 0 ? 0 : 1);

  printf("%ld\n", sum);

  return 0;
}
