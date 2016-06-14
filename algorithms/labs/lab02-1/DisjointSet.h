#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "Node.h"

class DisjointSet {
 public:

  void MakeSet(Node *node)
  {
    node->parent = node;
  }

  Node *Find(Node *x)
  {
    if (x->parent == x)
      return x;
    else
      return Find(x->parent);
  }

  void Union(Node *x, Node *y)
  {
    Node *xRoot = Find(x);
    Node *yRoot = Find(y);
    xRoot->parent = yRoot;
  }
};

#endif
