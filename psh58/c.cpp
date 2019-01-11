#include <stdio.h>
#include <algorithm>

int main(int argc, char *argv[])
{
	int t;
	int n, m;
	int x1, x2, x3, x4;
  int y1, y2, y3, y4;
	int w, b;
	int xi, yi, xa, ya;
	long long wa, ba, oa;

	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		scanf("%d %d %d %d", &x3, &y3, &x4, &y4);

		x1 -= 1;
		y1 -= 1;
		x3 -= 1;
		y3 -= 1;

		// get overlap region
		xi = std::max(x1, x3);
		yi = std::max(y1, y3);
		xa = std::min(x2, x4);
		ya = std::min(y2, y4);

		wa = (x2 - x1) * (y2 - y1);	// white area
		ba = (x4 - x3) * (y4 - y3); // black area
		oa = (xa - xi) * (ya - yi);	// overlap area

		printf("%lld %lld %lld\n", wa, ba, oa);

		// get original white and black tile count
		w = (n * m) / 2;
		b = w;

		w = w + (wa / 2) - (ba / 2) - (oa / 2);
		b = b - (wa / 2) + (ba / 2) + (oa / 2);

		if (oa == 1) {
			w = w + (((xi + yi) % 2) * -1) + (((xi + yi + 1) % 2) * 1); 
			b = b + (((xi + yi) % 2) * 1) + (((xi + yi + 1) % 2) * -1); 
		}

		printf("%d %d\n", w, b);
	}
	return 0;
}
