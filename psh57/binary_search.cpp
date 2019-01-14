#include <bits/stdc++.h>

using namespace std;

vector<int> s;

int main()
{
  int n;
  cin >> n;

  s = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  int l = 0, r = n;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (s[mid] == 0) {
      l = mid;
    } else {
      r = mid;
    }
  }

  if (s[r] == 0) {
    cout << r << endl;
  } else {
    cout << l << endl;
  }

  return 0;
}
