#include <stdio.h>

#define N_MAX   (100 + 1)

int arr_index = -1;
int arr[N_MAX];

void init() {
  arr_index = -1;
}

void push(int data) {
  if (arr_index == N_MAX - 1) return;
  arr[++arr_index] = data;
}

int pop() {
  if (arr_index == -1) return -1;
  return arr[arr_index--];
}

bool isEmpty() {
  return (arr_index == -1);
}

int main() {
  int t;
  int N;
  int data;

  scanf("%d", &t);
  for (int i = 0; i < t; ++t) {
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