#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX_ARRAY   (2*100000 + 1)

using namespace std;

int s[MAX_ARRAY];
int c[MAX_ARRAY] = {0,};
int r[MAX_ARRAY] = {0,};
int n, k;
int rc;

int can(int cnt)
{
  int i, j;

  rc = 0;
  for (i = 0; i < MAX_ARRAY; ++i) {
    int need = min(c[i] / cnt, k - rc);
    for (j = 0; j < need; ++j) {
      r[rc++] = i;
    }
  }

  return (rc == k);
}

int main(int argc, char *argv[])
{
  int i;

  scanf("%d %d", &n, &k);

  for (i = 0; i < n; ++i) {
    scanf("%d", &s[i]);
    c[s[i]]++;
  }

  int left = 0, right = n;
  while (right - left > 1) {
    int mid = (right + left) >> 1;
    if (can(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }

  if (!can(right))
    can(left);

  for (i = 0; i < rc; ++i) {
    printf("%d ", r[i]);
  }
  printf("\n");

  return 0;
}
