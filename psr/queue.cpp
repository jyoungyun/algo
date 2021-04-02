#include <stdio.h>

#define N_MAX       100

int arr_head;
int arr_tail;
int arr[N_MAX];

void init(void) {
    arr_head = 0;
    arr_tail = arr_head;
}

bool isFull(void) {
    if ((arr_head + 1) % N_MAX == arr_tail) {
        return true;
    } else {
        return false;
    }
}

bool isEmpty(void) {
    return arr_head == arr_tail;
}

int push(int data) {
    if (isFull()) return 1;
    arr[arr_head++] = data;
    if (arr_head > N_MAX) {
        arr_head = 0;
    }
    return 0;
}

int pop(void) {
    if (isEmpty()) return 1;
    return arr[arr_tail++];
}

int main() {
    int t;
    int N;
    int data;

    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        init();
        scanf("%d", &N);
        for (int j = 0; j < N; ++j) {
            scanf(" %d", &data);
            push(data);
        }

        while (isEmpty() == false) {
            printf("%d ", pop());
        }
        printf("\n");
    }
}