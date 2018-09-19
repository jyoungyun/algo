#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE    (100000 + 1)

struct Node {
  int data;
  struct Node *next;
};
struct Node adj[MAX_NODE];

typedef struct {
  int parent;
  struct Node *child;
} treeNode;
treeNode tree[MAX_NODE];
int N;

void initTree(void)
{
  int i;

  for (i = 0; i < N; ++i) {
    tree[i].parent = -1;
    tree[i].child = NULL;
  }
}

void addChild(int r, int c)
{
  struct Node *it, *n;

  it = tree[r].child;
  n = (struct Node*)malloc(1 * sizeof(struct Node));
  n->data = c;
  n->next = it;
  tree[r].child = n;

  tree[c].parent = r;
}

void makeTree(int root)
{
  struct Node *it;

  for (it = adj[root].next; it != NULL; it = it->next) {
    if (it->data != tree[root].parent) {
      addChild(root, it->data);
      makeTree(it->data);
    }
  }
}

void printTree(void)
{
  int i;
  struct Node *it;

  for (i = 1; i <= N; ++i) {
    printf("%d parent : %d\n", i, tree[i].parent);
    for (it = tree[i].child; it != NULL; it = it->next) {
      printf("(%d) -> ", it->data);
    }
    printf("\n");
  }
}

void addAdjList(int a, int b)
{
  struct Node *n;

  // Push a list
  n = (struct Node*)malloc(1 * sizeof(struct Node));
  n->data = b;
  n->next = adj[a].next;
  adj[a].next = n;

  // Push b list
  n = (struct Node*)malloc(1 * sizeof(struct Node));
  n->data = a;
  n->next = adj[b].next;
  adj[b].next = n;
}

void printAdjList(void)
{
  int i;
  struct Node *it;

  for (i = 1; i <= N; ++i) {
    printf("%d\n", i);
    for (it = adj[i].next; it != NULL; it = it->next) {
      printf("(%d) -> ", it->data);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  int i, a, b, k;

  scanf("%d", &N);

  initTree();

  for (i = 0; i < N-1; ++i) {
    scanf("%d %d", &a, &b);
    addAdjList(a, b);
  }

  makeTree(1);

  for (i = 2; i <= N; ++i) {
    printf("%d\n", tree[i].parent);
  }

  return 0;
}
