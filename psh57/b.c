#include <stdio.h>

#define MAX_INT   (100)

int main(int argc, char *argv[])
{
  int n;
  int a[MAX_INT + 2] = {0,};
  int c[MAX_INT + 2] = {0,};
  int i;
  int t = 0;

  scanf("%d", &n);
  for (i = 1; i < n + 1; ++i) {
    scanf("%d", &a[i]);
  }

#ifdef __DEBUG__
  for (i = 0; i < n + 2; ++i) {
    printf("%d ", a[i]);
  }
#endif

  for (i = 1; i < n + 1; ++i) {
    if (a[i] == 0 && // Want to sleep
        (a[i - 1] == 1 && a[i + 1] == 1) && // Disturbed!!!
        (c[i - 1] == 0 && c[i + 1] == 0)) {   // Not checked
      t++;
      c[i - 1] = 1;
      c[i + 1] = 1;
    }
  }

  printf("%d\n", t);

  return 0;
}
