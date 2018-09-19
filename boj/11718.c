#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char ch;

  while ((ch = getchar()) != EOF) {
    putchar(ch);
  }

  return 0;
}
