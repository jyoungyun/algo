#include <stdio.h>

#define MAX_ARRAY   (200000)

long long a[MAX_ARRAY];
int r[MAX_ARRAY];

int main(int argc, char *argv[])
{
  int n;
  int i, j;
  long long t = 0;
  int cnt = 0;
  int m1 = 0, m2 = 0;
  int m;

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    t += a[i];

    if (m1 < a[i]) {
      m2 = m1;
      m1 = a[i];
    } else if (m2 < a[i]) {
      m2 = a[i];
    }
  }

  for (i = 0; i < n; ++i) {
    if (a[i] == m1) {
      m = m2;
    } else {
      m = m1;
    }

    if ((t - a[i]) - (2 * m) == 0) {
      r[cnt++] = i + 1;
    }
  }

  printf("%d\n", cnt);
  for (i = 0; i < cnt; ++i) {
    printf("%d ", r[i]);
  }
  printf("\n");

  return 0;
}
