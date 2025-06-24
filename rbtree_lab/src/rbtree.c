#include "rbtree.h"

#include <stdlib.h>

// typedef enum
// {
//   RBTREE_BLACK,
//   RBTREE_RED,
// } color_t;

// //
// typedef int key_t;

// //
// typedef struct node_t
// {
//   color_t color;
//   key_t key;
//   struct node_t *parent, *left, *right;
// } node_t;

//
// typedef struct
// {
//   node_t *root;
//   node_t *nil;
// } rbtree;

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t)); // 힙 영역에 남겨놓기 위해서

  // nil_node를 calloc으로 초기화를 하면 node_t에 있는 멤버 변수들이 모두 초기화가 되는 건가? 0으로 초기화가 되는 건가?
  // -> yes
  // NULL 대신 nil_node로 설정, 전체가 자기 자신인 거임.
  nil_node->left = nil_node->right = nil_node->parent = nil_node;

  nil_node->color = RBTREE_BLACK;

  p->nil = nil_node;
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory

  free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
  // 선들이 추상적인 부분이 있음.
  // 혹시 끊어지지 않은 포인터나 연결이 있나? 걱정 될 수도.
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil)
  {
    t->root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil)
  {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == t->nil)
  {
    t->root = x;
  }
  else if (y == y->parent->left)
  {
    y->parent->left = x;
  }
  else
  {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{

  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  node_t *cur = t->nil;
  // node_t *cur = (node_t *)calloc(1, sizeof(node_t));
  node_t *pre = t->nil;
  // node_t *tmp = t->nil;
  // color_t tmp_color;
  new_node->key = key;
  new_node->color = RBTREE_RED;
  new_node->left = t->nil;
  new_node->right = t->nil;
  cur = t->root;
  pre = t->nil;

  if (cur == t->nil)
  {
    t->root = new_node;
    new_node->color = RBTREE_BLACK;
    // t->root->key = key;
    new_node->parent = t->nil;

    return t->root;
  }

  while (cur != t->nil)
  {
    pre = cur;
    if (cur->key < key)
    {
      cur = cur->right;
    }
    else
    {
      cur = cur->left;
    }
  }

  new_node->parent = pre;

  if (pre->key < new_node->key)
  {
    pre->right = new_node;
  }
  else
  {
    pre->left = new_node;
  }

  // z의 두 자식은 모두 경계 노드이다.
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  // case.1 부모/삼촌 노드가 모두 RED
  //  부모 삼촌을 모두  BLACK로 바꾸고, 할아버지를 RED로 수정

  while (new_node->parent->color == RBTREE_RED)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      pre = new_node->parent->parent->right; // new_node의 부모
      if (pre->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        pre->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
        // new_node는 현재 노드를 가르키는 포인터이구나..!
      }
      else
      {
        // CASE.2 꺾여있는 노드를 펴준다.
        if (new_node == new_node->parent->right)
        {
          new_node = new_node->parent; // 이렇게 할당해도 되는 건가?
          // 포인터를 할당처럼 생각하는 것. 포인터이기 때문에 해당 주소를 바라보게 만드는 것 뿐.
          // 기존에 있던 노드를 덮어쓰는 것이 아니다 ?!
          left_rotate(t, new_node);
        }
        // CASE.3
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        // 수정
        // right_rotate(t, new_node);
        right_rotate(t, new_node->parent->parent);
      }
    }
    else
    {
      pre = new_node->parent->parent->left;
      if (pre->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        pre->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else
      {
        if (new_node == new_node->parent->left)
        {
          new_node = new_node->parent;
          right_rotate(t, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        // 수정
        left_rotate(t, new_node);
        // 그냥 바로 left_rotate를 하면 왜 문제가 생기는 거지?
        // left_rotate(t, new_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return t->root;
}

// while (cur->parent->color == RBTREE_RED)
// {
//   if (pre->parent->left->color == RBTREE_RED && pre->parent->right->color == RBTREE_RED)
//   {

//     pre->parent->left->color = RBTREE_BLACK;
//     pre->parent->right->color = RBTREE_BLACK;
//     pre->parent->color = RBTREE_RED;

//     // 할아버지에서 다시 시작 ? 할아버지에서 다시 시작이 뭐지 왜 필요한거지?
//     // 아래 방향성이 맞나 ?
//     cur = pre->parent;
//     // pre = cur->parent;
//   }
//   else
//   {
//     // case.2 할아버지/부모/자신 꺾인 상태 -> 회전을 통해 CASE.3로 만들어준다.

//     if (pre->parent->key > pre->key && pre->key < cur->key)
//     {
//       cur->parent = pre->parent;
//       pre->parent->left = cur;
//       cur->left = pre;
//       pre->left = t->nil;
//       pre->right = t->nil;
//     }
//     else if (pre->parent->key < pre->key && pre->key > cur->key)
//     {
//       cur->parent = pre->parent;
//       pre->parent->right = cur;
//       cur->right = pre;
//       pre->left = t->nil;
//       pre->right = t->nil;
//     }

//     // case.3 할아버지/부모/자신 펴진 상태

//     tmp_color = cur->color;
//     cur->color = cur->parent->color;
//     cur->parent->color = tmp_color;

//     // if (cur->key < cur->parent->key)
//     // {
//     if (pre->parent->parent != NULL)
//     {
//       if (pre->parent->parent->key < pre->parent->key)
//       {
//         pre->parent->parent->right = cur->parent;

//         pre->right = pre->parent;
//         pre->parent->left = t->nil;
//       }
//       else
//       {
//         pre->parent->parent->left = cur->parent;

//         pre->left = pre->parent;
//         pre->parent->right = t->nil;
//       }
//       pre->parent = pre->parent->parent;
//       pre->parent->parent = pre;
//     }
//     // }
//   }
// }

// t->root->color = RBTREE_BLACK;
// return t->root;
// }

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *answer = t->root;
  // while (answer->left != t->nil)
  // {
  //   if (answer->key > answer->left->key) // t->nil이 될 때까지 가장 왼쪽으로 노드를 찾는 방식이 좀 더 효율적이다.
  //   {
  //     answer = answer->left;
  //   }
  // }

  if (answer == t->nil)
  {
    return t->root;
  }

  while (answer->left != t->nil)
  {
    answer = answer->left;
  }
  // t->root를 반환하는게 맞나?
  // answer에 포인터를 할당했으니, 같은 곳을 바라보게 만드는게 맞는건가?
  // return t->root;
  return answer;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *answer = t->root;

  if (answer == t->nil)
  {
    return t->root;
  }

  while (answer->right != t->nil)
  {
    answer = answer->right;
  }

  return answer;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}