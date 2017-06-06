#include <iostream>
#include <string>
using namespace std;
class Node {
public:
Node * next;
Node * previous;
int data;
Node();
Node(int );
};
Node::Node()
{
  data =0;
  next=NULL;
  previous=NULL;
}
Node::Node(int i)
{
  data=i;
  next=NULL;
  previous=NULL;
}

class ARTraverser {
protected:
  Node * current;
public:
  virtual bool hasNode();
  virtual Node * next();

};
class ARTF:public ARTraverser{
public:
  bool hasNode();
  Node * next();
};


class AdderRemover{
protected:
  Node * head;
  Node * tail;
  string name;
  int nodeCount;
  ARTraverser * traverser;
public:
  void add(int i);
  void remove();
  void setTraverser();
  void display();
  void removeAll();
  void traverse();
};
