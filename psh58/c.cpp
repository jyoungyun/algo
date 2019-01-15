#include <cstdio>
#include <iostream>
#include <algorithm>

long long getwhite(int x1, int y1, int x2, int y2)
{
  int n = y2 - y1 + 1;
  int m = x2 - x1 + 1;
  long long w;

  w = (long long)(n*m) / 2;
  if ((n%2) && (m%2) && ((long long)(x1+y1)%2) == 0)
    w += 1;
  return w;
}

long long getblack(int x1, int y1, int x2, int y2)
{
  int n = y2 - y1 + 1;
  int m = x2 - x1 + 1;

  return (long long)(n*m) - getwhite(x1, y1, x2, y2);
}

int main(int argc, char *argv[])
{
  int t;
  int n, m;
  int x1, y1, x2, y2, x3, y3, x4, y4;
  int ox1, oy1, ox2, oy2;     // overlap area
  long long w;

  scanf("%d", &t);

  while (t--) {
    scanf("%d %d", &n, &m);   // n : row, m : column

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    scanf("%d %d %d %d", &x3, &y3, &x4, &y4);

    ox1 = std::max(x1, x3);
    oy1 = std::max(y1, y3);
    ox2 = std::min(x2, x4);
    oy2 = std::min(y2, y4);

    if (ox1 > ox2 || oy1 > oy2)
      w = getwhite(1, 1, m, n) + getblack(x1, y1, x2, y2) - getwhite(x3, y3, x4, y4);
    else
      w = getwhite(1, 1, m, n) + getblack(x1, y1, x2, y2) - getblack(ox1, oy1, ox2, oy2) - getwhite(x3, y3, x4, y4);

    std::cout << w << " " << (long long)(n*m) - w << std::endl;
  }
  return 0;
}
