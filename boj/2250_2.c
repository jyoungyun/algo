#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE    (10000 + 1)
#define INF         987654321

#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

struct Node {
  int idx;
  struct Node *left;
  struct Node *right;
};
struct Node *arr[MAX_NODE];
int N;

int isChild[MAX_NODE];

int idx = 1;
int mn, mx;
int maxLevel = 1;

void dfs(struct Node **current)
{
  if ((*current)->left != NULL) {
    dfs(&(*current)->left);
  }

  (*current)->idx = idx++;

  if ((*current)->right != NULL) {
    dfs(&(*current)->right);
  }
}

void levelOrder(struct Node **current, int d, int level)
{
  if (d == level) {
    mn = MIN(mn, (*current)->idx);
    mx = MAX(mx, (*current)->idx);
  }
  if ((*current)->left != NULL) {
    levelOrder(&(*current)->left, d + 1, level);
  }
  if ((*current)->right != NULL) {
    levelOrder(&(*current)->right, d + 1, level);
  }
}

int main(int argc, char *argv[])
{
  int i, root, left, right, h, ret, retidx;

  scanf("%d", &N);

  for (i = 1; i <= N; ++i) {
    arr[i] = (struct Node*)malloc(1 * sizeof(struct Node));
    arr[i]->idx = -1;
    arr[i]->left = arr[i]->right = NULL;
  }

  for (i = 1; i <= N; ++i) {
    scanf("%d %d %d", &root, &left, &right);
    if (left != -1) {
      arr[root]->left = arr[left];
      isChild[left] = 1;
    }
    if (right != -1) {
      arr[root]->right = arr[right];
      isChild[right] = 1;
    }
  }

  root = 0;
  for (i = 1; i <= N; ++i) {
    if (isChild[i] == 0) {
      root = i;
      break;
    }
  }

  dfs(&arr[root]);

  ret = 0;
  retidx = -1;
  for (i = 1; i <= N; ++i) {
    mn = INF;
    mx = -INF;
    levelOrder(&arr[root], 1, i);

    if (ret < mx - mn + 1) {
      ret = mx - mn + 1;
      retidx = i;
    }
  }

  printf("%d %d\n", retidx, ret);

  return 0;
}
