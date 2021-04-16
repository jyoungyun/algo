#include <stdio.h>

#define MAX_SIZE     100

int heap[MAX_SIZE + 1];
int heapSize = 1;

void heapInit(void)
{
    heapSize = 1;
}

int heapPush(int value)
{
    if (heapSize + 1 > MAX_SIZE) {
        printf("heap full");
        return 0;
    }

    heap[heapSize] = value;

    int current = heapSize;
    while (current > 1 && heap[current] < heap[current/2]) {
        int temp = heap[current];
        heap[current] = heap[current/2];
        heap[current/2] = temp;
        current = current / 2;
    }
    heapSize++;
}

int heapPop()
{
    if (heapSize == 1) {
        printf("heap empty");
        return 0;
    }

    int temp = heap[1];
    heapSize--;

    heap[1] = heap[heapSize];

    int current = 1;
    while (current * 2 < heapSize) {
        int child;
        if (current * 2 + 1 == heapSize) {
            child = current *2;
        } else {
            child = heap[current * 2] < heap[current * 2 + 1] ? current * 2 : current*2+1;            
        }

        if (heap[current] < heap[child]) {
            break;
        }
        int temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;

        current = child;
    }
    return temp;
}

int main()
{
    int T;
    int N;
    int v;

    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        heapInit();
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &v);
            heapPush(v);
        }
        printf("#%d ", t);
        for (int i = 0; i < N; ++i) {
            printf("%d ", heapPop());
        }
        printf("\n");
    }
}