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

  // p->nil->key = NULL;

  // p->root = NULL;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{

  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  node_t *cur = (node_t *)calloc(1, sizeof(node_t));
  // node_t *pre = (node_t *)calloc(1, sizeof(node_t));
  node_t *pre = t->nil;
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
    t->root->key = key;

    return t->root;
    // new_node->parent = t->root;
  }

  while (cur != t->nil)
  {
    pre = cur;
    if (cur->key < key)
    {
      // if (cur->right == t->nil)
      // {
      //   cur->right = new_node;
      //   cur->right->parent = cur;
      // }
      cur = cur->right;
    }
    else
    {
      // if (cur->left == t->nil)
      // {
      //   cur->left = new_node;
      //   cur->left->parent = cur;
      // }
      cur = cur->left;
    }
  }

  cur = new_node;
  new_node->parent = pre;

  if (pre->key < new_node->key)
  {
    pre->right = new_node;
  }
  else
  {
    pre->left = new_node;
  }

  // new_node->parent = cur;

  // 탐색 과정에서
  // if (t->root == t->nil)
  // {
  //   // 루트를 변경하면 안 됨.
  //   // t->root->key = key;
  //   // t->root->left = t->nil;
  //   // t->root->right = t->nil;

  //   // t->root = new_node;
  //   // t->nil = new_node;
  //   t->root = new_node;
  //   // new_node->left = t->nil;
  //   // new_node->right = t->nil;
  //   new_node->parent = t->root;
  //   // cur = t->root;
  // }
  // else
  // {
  //   while (cur != t->nil)
  //   {
  //     if (cur->key < key)
  //     {
  //       if (cur->right == t->nil)
  //       {
  //         cur->right = new_node;
  //         cur->right->parent = cur->right;
  //       }
  //       else
  //       {
  //         cur = cur->right;
  //       }
  //       // new_node->parent = cur;
  //     }
  //     else
  //     {
  //       if (cur->left == t->nil)
  //       {
  //         cur->left = new_node;
  //         cur->left->parent = cur->left;
  //       }
  //       else
  //       {
  //         cur = cur->left;
  //       }
  //     }
  //     // new_node->parent = cur;
  //   }
  // }
  return t->root;
}

// 첫번째 시도
// node_t *rbtree_insert(rbtree *t, const key_t key)
// {

//   // if (t->root->key == NULL)
//   // {
//   //   t->root->key = key;
//   // }
//   node_t *prev = t->nil;
//   node_t *nxt = t->nil;
//   node_t *new_node = (node_t *)malloc(sizeof(new_node)); // 노드 동적 할당
//   // new_node = t->nil;
//   new_node->key = key;
//   new_node->color = RBTREE_RED;

//   nxt = t->root;

//   if (t->root == t->nil)
//   {
//     t->root->key = key;
//     // t->nil->left = NULL;
//     // t->nil->right = NULL;

//     t->root->left = t->nil;
//     t->root->right = t->nil;
//   }
//   else
//   {
//     while (nxt != t->nil)
//     {
//       if (nxt->key < key)
//       {
//         prev = nxt;
//         nxt = nxt->left;
//       }
//       else
//       {
//         prev = nxt;
//         nxt = nxt->right;
//       }
//     }
//   }

//   if (prev->color == RBTREE_BLACK)
//   {
//     if (prev->key < key)
//     {
//       t->root->right = new_node;
//     }
//     else
//     {
//       t->root->left = new_node;
//     }
//   }
//   else
//   {
//     // Case.1

//     // Case.2

//     // Case.3
//   }

//   return t->root;
// }

// node_t *rbtree_find(const rbtree *t, const key_t key)
// {
//   // TODO: implement find
//   return t->root;
// }

// node_t *rbtree_min(const rbtree *t)
// {
//   // TODO: implement find
//   return t->root;
// }

// node_t *rbtree_max(const rbtree *t)
// {
//   // TODO: implement find
//   return t->root;
// }

// int rbtree_erase(rbtree *t, node_t *p)
// {
//   // TODO: implement erase
//   return 0;
// }

// int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
// {
//   // TODO: implement to_array
//   return 0;
// }
