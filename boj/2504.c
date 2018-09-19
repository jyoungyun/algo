#include <stdio.h>

#define true  1
#define false 0

#define CHAR  0x40000000
#define GET_VALUE(x)    ((x) == ')' ? 2 : 3)

#define MAX 30
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

int top(void)
{
  return stack[idx - 1];
}

int size(void)
{
  return idx;
}

void print(void)
{
  int i;
  printf("total idx : %d\n", idx);
  for (i = 0; i < idx; ++i) {
    if (stack[i] & CHAR) {
      printf("%c ", stack[i] & ~CHAR);
    } else {
      printf("%d ", stack[i]);
    }
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int i, s, t, err = false;
  char c;
  char str[MAX];

  scanf("%s", str);
  for (i = 0; str[i] != '\0'; ++i) {
    c = str[i];
    if (c != '(' && c != ')' && c != '[' && c != ']') {
      err = true;
      break;
    }
    if (c == '(' || c == '[') {
      push(c | CHAR);
    } else if (c == ')' || c == ']') {
      // if (number), sum all of numbers until bracket
      s = 0;
      while (size() != 0 && !(top() & CHAR)) {
        s += pop();
      }
      // bracket
      t = (pop() & ~CHAR);
      if (c == ')' && t != '(') {
        err = true;
        break;
      } else if (c == ']' && t != '[') {
        err = true;
        break;
      }
      if (s != 0) {
        push(s * GET_VALUE(c));
      } else {
        push(GET_VALUE(c));
      }
    }
//    print();
  }

  s = 0;
  if (err != true) {
    while (size() != 0 && !(top() & CHAR)) {
      s += pop();
    }
    if (size() != 0) {
      s = 0;
    }
  }
  printf("%d\n", s);
  return 0;
}
