#include <stdio.h>

#define MAX_DATA  100

int N;
int arr[MAX_DATA + 1];

void insertionSort()
{
  int t;

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (arr[i] > arr[j]) {
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
      }
    }
  }
}

int main()
{
  int T;

  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &arr[i]);
    }
    printf("#%d ", t);
    insertionSort();
    for (int i = 0; i < N; ++i) {
      printf("%d ", arr[i]);
    }
    printf("\n");
  }
}
