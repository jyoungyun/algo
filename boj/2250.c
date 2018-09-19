#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE    (10000 + 1)
#define INF         (987654321)

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

void dfs(struct Node **cur)
{
  if ((*cur)->left != NULL) {
    dfs(&(*cur)->left);
  }

  (*cur)->idx = idx++;

  if ((*cur)->right != NULL) {
    dfs(&(*cur)->right);
  }
}

void levelOrder(struct Node **cur, int d, int level)
{
  if (d == level) {
    mn = MIN(mn, (*cur)->idx);
    mx = MAX(mx, (*cur)->idx);
  }

  if ((*cur)->left != NULL) {
    levelOrder(&(*cur)->left, d + 1, level);
  }
  if ((*cur)->right != NULL) {
    levelOrder(&(*cur)->right, d + 1, level);
  }
}

int main(int argc, char *argv[])
{
  int i, root, left, right, ret, retidx;

  scanf("%d", &N);

  for (i = 1; i <= N; ++i) {
    arr[i] = (struct Node *)malloc(1 * sizeof(struct Node));
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

  for (i = 1; i <= N; ++i) {
    if (isChild[i] == 0) {
      root = i;
      break;
    }
  }

  dfs(&arr[root]);

  ret = retidx = 0;
  for (i = 1; i <= MAX_NODE; ++i) {
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
