#ifndef NODE_H
#define NODE_H

class Node {
 public:
  int element;
  Node *parent;

 Node(int element):element(element) {}
};

#endif
