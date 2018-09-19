#include <stdio.h>

#define MAX 50
int idx;
int stack[MAX];

void push(int v)
{
  if (idx == MAX) {
    return;
  }
  stack[idx++] = v;
}

int pop(void)
{
  int v;
  if (idx == 0) {
    return -1;
  }
  v = stack[idx - 1];
  idx--;
  return v;
}

int size(void)
{
  return idx;
}

void reset(void)
{
  idx = 0;
}

int main(int argc, char *argv[])
{
  int n, i, r;
  char str[MAX];

  scanf("%d", &n);
  while(n--) {
    scanf("%s", str);
    for (i = 0; str[i] != '\0'; i++) {
      if (str[i] == '(') {
        push(1);
      } else if (str[i] == ')') {
        r = pop();
        if (r == -1) {
          break;
        }
      }
    }

    if (r < 0 || size() != 0) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }

    reset();
  }
  return 0;
}
