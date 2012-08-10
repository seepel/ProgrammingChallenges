#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Node;

typedef string::iterator StrIter;
typedef vector<Node>::const_iterator NodeIter;

class Node {
  public:
    StrIter begin;
    StrIter end;
    vector<Node> children;

    static Node *activeNode;

    Node() {
      Node *activeNode = this;
    };

    void addSuffix(StrIter suffix) {
      bool found = false;
      for(int i=0; i!= children.size(); i++) {
        if(children[i].children.size() == 0)
          children[i].end = suffix;
        if(*(children[i].begin) == *suffix)
          found = true;
      }
      if(!found) {
        Node node;
        node.begin = suffix;
        node.end = suffix+1;
        children.push_back(node);
      }
    };

    void print() {
      queue<NodeIter> nodes;
      for(NodeIter node = children.begin(); node != children.end(); node++)
        nodes.push(node);
      while(!nodes.size() == 0) {
        NodeIter node = nodes.front();
        for(StrIter c = node->begin; c != node->end; c++)
          cout << *c;
        cout << endl;
        for(NodeIter child = node->children.begin(); child != node->children.end(); child++)
          nodes.push(child);
        nodes.pop();
      }
    };

};

using namespace std;

int main(void) {
  string word = "abcabx";
  Node root;
  for(StrIter c=word.begin(); c!=word.end(); c++) {
    root.addSuffix(c);
  }

  root.print();
  return 0;
}
