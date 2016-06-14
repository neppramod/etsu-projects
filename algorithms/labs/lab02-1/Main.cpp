#include "DisjointSet.h"

#include <vector>
#include <iostream>

using namespace std;

void printNode(Node *node)
{
  Node *cur = node;

  cout << cur->element << endl;
  
  if (node == node->parent)
    return;
  else
    printNode(node->parent);    
}

int main(int argc, char *argv[])
{
  DisjointSet disJointSet;
  vector<Node> nodes;

  Node *node1 = new Node(1);
  disJointSet.MakeSet(node1);
  nodes.push_back(*node1);

  Node *node2 = new Node(2);
  disJointSet.MakeSet(node2);
  nodes.push_back(*node2);

  for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it)
  {
    Node nd = *it;
    cout << nd.element << endl;
  }

  disJointSet.Union(node1, node2);

  printNode(node1);
    
  return 0;
}
