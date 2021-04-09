#include <stdio.h>

#define MAX_VERTEX 30

int vertex;
int map[MAX_VERTEX][MAX_VERTEX];
int visit[MAX_VERTEX];
// bfs
int queue[MAX_VERTEX];
int front, rear;

void depthFirstSearch(int v)
{
    int i;
    visit[v] = 1;
    for (i = 1; i <= vertex; ++i) {
        if (map[v][i] == 1 && !visit[i]) {
            printf("%d ", i);
            depthFirstSearch(i);
        }
    }
}

// int breadFirstSearch(int v)
// {
//     int i;
//     int t;

//     visit[v] = 1;
//     printf("%d ", v);
//     queue[rear++] = v;
//     while (front < rear) {
//         t = queue[front++];
//         for (i = 1; i <= vertex; i++) {
//             if (map[t][i] == 1 && !visit[i]) {
//                 visit[i] = 1;
//                 printf("%d ", i);
//                 queue[rear++] = i;
//             }
//         }
//     }
// }

int breadFirstSearch(int v) {
    printf("%d ", v);
    for (int i = 1; i <= vertex; ++i) {
        if (map[v][i] == 1 && !visit[i]) {
            visit[i] = 1;
            queue[rear++] = i;
        }
    }
    while (front < rear) {
        breadFirstSearch(queue[front++]);
    }
}

int main(void) {
    int T;
    int start;
    int v1, v2;

    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
        scanf("%d %d", &vertex, &start);

        for (int i = 1; i <= vertex; ++i) {
            for (int j = 1; j <= vertex; ++j) {
                map[i][j] = 0;
            }
            visit[i] = 0;
        }

        while (1) {
            scanf("%d %d", &v1, &v2);
            if (v1 == v2 && v1 == -1)
                break;

            map[v1][v2] = map[v2][v1] = 1;
        }

        printf("#%d ", t);
        // printf("%d ", start);
        visit[1] = 1;
        breadFirstSearch(start);
        printf("\n");
    }   
}
