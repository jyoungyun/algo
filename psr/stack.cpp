#include <stdio.h>

#define N_MAX   (100)

int arr_index;
int arr[N_MAX];

void init() {
  arr_index = 0;
}

int push(int data) {
  if (arr_index == N_MAX) return 1;
  arr[arr_index++] = data;
  return 0;
}

int pop(void) {
  if (arr_index == 0) return -1;
  return arr[--arr_index];
}

bool isEmpty() {
  return (arr_index == 0);
}

int main() {
  int t;
  int N;
  int data;

  scanf("%d", &t);
  for (int i = 0; i < t; ++t) {
    init();
    scanf("%d", &N);
    for (int j = 0; j < N; ++j) {
      scanf(" %d", &data);

      push(data);
    }

    while (isEmpty() == false) {
      printf("%d ", pop());
    }
  }
}