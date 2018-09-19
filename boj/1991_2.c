#include <stdio.h>

#define MAX_NODE    26
#define MAX_CHILD   2

struct treeNode {
  int parent;
  int child[MAX_CHILD];
};
struct treeNode tree[MAX_NODE];
int nodeNum;

void initTree(void)
{
  int i, j;

  for (i = 0; i <= nodeNum; ++i) {
    tree[i].parent = -1;
    for (j = 0; j < MAX_CHILD; ++j) {
      tree[i].child[j] = -1;
    }
  }
}

void addChild(int p, int c1, int c2)
{
  int pi, ci;

  pi = p - 'A';

  if (c1 != '.') {
    ci = c1 - 'A';
    tree[pi].child[0] = ci;
    tree[ci].parent = pi;
  }

  if (c2 != '.') {
    ci = c2 - 'A';
    tree[pi].child[1] = ci;
    tree[ci].parent = pi;
  }
}

int getRoot(void)
{
  int i;

  for (i = 0; i <= nodeNum; ++i) {
    if (tree[i].parent == -1)
      return i;
  }
  return -1;
}

void preOrder(int root)
{
  int i, child;

  printf("%c", root + 'A');
  for (i = 0; i < MAX_CHILD; ++i) {
    child = tree[root].child[i];
    if (child != -1) {
      preOrder(child);
    }
  }
}

void inOrder(int root)
{
  int child;

  child = tree[root].child[0];
  if (child != -1) {
    inOrder(child);
  }
  printf("%c", root + 'A');
  child = tree[root].child[1];
  if (child != -1) {
    inOrder(child);
  }
}

void postOrder(int root)
{
  int i, child;

  for (i = 0; i < MAX_CHILD; ++i) {
    child = tree[root].child[i];
    if (child != -1) {
      postOrder(child);
    }
  }
  printf("%c", root + 'A');
}
int main(int argc, char *argv[])
{
  int i, r;
  char p, c1, c2;

  scanf("%d", &nodeNum);

  initTree();

  for (i = 0; i < nodeNum; ++i) {
    scanf(" %c %c %c", &p, &c1, &c2);
    addChild(p, c1, c2);
  }

  r = getRoot();
  preOrder(r);
  printf("\n");
  inOrder(r);
  printf("\n");
  postOrder(r);
  printf("\n");
  return 0;
}
