#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE    (100000 + 1)

struct Node {
  int vertex;
  int distance;
  struct Node *next;
};
struct Node adj[MAX_NODE];

struct treeNode {
  struct Node *padj;
  struct treeNode *next;
};

typedef struct {
  int parent;
  struct treeNode *child;
} treeNode;
treeNode tree[MAX_NODE];
int N;

int dist[MAX_NODE];

void addAdjList(int idx, int v, int d)
{
  struct Node *n;

  n = (struct Node*)malloc(1 * sizeof(struct Node));
  n->vertex = v;
  n->distance = d;
  n->next = adj[idx].next;
  adj[idx].next = n;
}

void printAdjList(void)
{
  int i;
  struct Node *it;

  for (i = 1; i <= N; ++i) {
    printf("[%d] ", i);
    for (it = adj[i].next; it != NULL; it = it->next) {
      printf("(%d) -> ", it->vertex);
    }
    printf("\n");
  }
}

void initTree(void)
{
  int i;

  for (i = 1; i <= N; ++i) {
    tree[i].parent = -1;
    tree[i].child = NULL;
  }
}

void addChild(int root, struct Node *data)
{
  struct treeNode *n;

  n = (struct treeNode*)malloc(1 * sizeof(struct treeNode));
  n->padj = data;
  n->next = tree[root].child;
  tree[root].child = n;

  tree[data->vertex].parent = root;
}

void makeTree(int root)
{
  struct Node *it;

  for (it = adj[root].next; it != NULL; it = it->next) {
    if (it->vertex != tree[root].parent) {
      addChild(root, it);
      makeTree(it->vertex);
    }
  }
}

void printTree(void)
{
  int i;
  struct treeNode *it;

  for (i = 1; i <= N; ++i) {
    printf("%d parent : %d\n", i, tree[i].parent);
    for (it = tree[i].child; it != NULL; it = it->next) {
      printf("(%d:%d) -> ", it->padj->vertex, it->padj->distance);
    }
    printf("\n");
  }
}

int getSum(int root)
{
  int save = 0, save2;
  int ret;
  struct treeNode *it;

  if (tree[root].child == NULL) {
    return 0;
  }

  for (it = tree[root].child; it != NULL; it = it->next) {
    ret = getSum(it->padj->vertex) + it->padj->distance;
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
  int i, idx, v, d;

  scanf("%d", &N);

  initTree();

  for (i = 0; i < N; ++i) {
    scanf("%d", &idx);
    while (1) {
      scanf("%d", &v);
      if (v == -1)
        break;
      scanf("%d", &d);
      addAdjList(idx, v, d);
    }
  }

//  printAdjList();

  makeTree(1);

//  printTree();

  printf("%d\n", getMaxSum());

  return 0;
}

