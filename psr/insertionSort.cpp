#include <stdio.h>

#define MAX_DATA  100

int N;
int arr[MAX_DATA + 1];

void insertionSort()
{
  int t;
  int j;

  for (int i = 1; i < N; ++i) {
    t = arr[i];
    j = i - 1;
    while(t < arr[j] && j >= 0) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = t;
  }

//  for (int i = 1; i < N; ++i) {
//    for (int j = i + 1; j < N; ++j) {
//      if (arr[i] > arr[j]) {
//        t = arr[i];
//        arr[i] = arr[j];
//        arr[j] = t;
//      }
//    }
//  }
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
