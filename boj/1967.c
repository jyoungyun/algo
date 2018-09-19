#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE  10000

struct Node {
  int data;
  int distance;
  struct Node *next;
};

typedef struct {
  int parent;
  struct Node *child;
} treeNode;
treeNode tree[MAX_NODE];
int N;

int dist[MAX_NODE];

void initTree(void)
{
  int i;

  for (i = 1; i <= N; ++i) {
    tree[i].parent = -1;
    tree[i].child = NULL;
  }
}

void addChild(int r, int c, int d)
{
  struct Node *n;

  n = (struct Node*)malloc(1 * sizeof(struct Node));
  n->data = c;
  n->distance = d;
  n->next = tree[r].child;
  tree[r].child = n;
}

int getSum(int root)
{
  struct Node *it;
  int ret, save = 0, save2;

  if (tree[root].child == NULL) {
    return 0;
  }

  for (it = tree[root].child; it != NULL; it = it->next) {
    ret = getSum(it->data) + it->distance;
    if (ret > save) {
      save2 = save;
      save = ret;
    } else if (ret > save2) {
      save2 = ret;
    }
  }

  dist[root] = save + save2;

  return save;
}

int getMaxSum(void)
{
  int i, max = 0;

  getSum(1);

  for (i = 1; i <= N; ++i) {
    if (dist[i] > max) {
      max = dist[i];
    }
  }

  return max;
}

int main(int argc, char *argv[])
{
  int i, r, c, d;

  scanf("%d", &N);

  initTree();

  for (i = 0; i < N - 1; ++i) {
    scanf("%d %d %d", &r, &c, &d);
    addChild(r, c, d);
  }

  printf("%d\n", getMaxSum());

  return 0;
}
