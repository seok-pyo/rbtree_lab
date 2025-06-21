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

  nil_node->left = nil_node->right = nil_node->parent = NULL;
  nil_node->color = RBTREE_BLACK;

  p->nil = nil_node;
  p->root = p->nil;

  // p->nil->key = NULL;

  // p->root = NULL;

  return p;
}

// void delete_rbtree(rbtree *t)
// {
//   // TODO: reclaim the tree nodes's memory
//   free(t);
// }

node_t *rbtree_insert(rbtree *t, const key_t key)
{

  // if (t->root->key == NULL)
  // {
  //   t->root->key = key;
  // }
  if (t->root == t->nil)
  {
    t->root->key = key;
  }
  else
  {
    while (t->root != t->nil)
    {
      if (t->root->key < key)
      {
        t->root = t->root->left;
      }
      else
      {
        t->root = t->root->right;
      }
    }
  }

  return t->root;
}

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
