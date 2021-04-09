#include <stdio.h>

#define N       100
#define INF     100000

int map[N + 1][N + 1];
int dist[N + 1];
int visit[N + 1];
int vertex;

void dijkstra()
{
    int min;
    int v;

    for (int i = 1; i <= vertex; ++i) {
        min = INF;
        for (int j = i; j <= vertex; ++j) {
            if (!visit[j] && min > dist[j]) {
                min = dist[j];
                v = j;
            }
        }
        visit[v] = 1;
        for (int j = i; j <= vertex; ++j) {
            if (dist[j] > dist[v] + map[v][j]) {
                dist[j] = dist[v] + map[v][j];
            }
        }
    }
}

int main() {
    int T;
    int start;
    int end;
    int edge;
    int v1, v2, cost;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d %d %d", &vertex, &start, &end);

        for (int i = 1; i <= vertex; ++i) {
            for (int j = 1; j <= vertex; ++j) {
                if (i != j) {
                    map[i][j] = INF;
                }
            }
            dist[i] = INF;
            visit[i] = 0;
        }

        scanf("%d", &edge);
        for (int j = 1; j <= edge; ++j) {
            scanf("%d %d %d", &v1, &v2, &cost);
            map[v1][v2] = cost;
        }

        printf("#%d ", t);
        dist[start] = 0;
        dijkstra();
        printf("%d\n", dist[end]);
    }
}