#include <iostream>
#include <string>
#include <vector>

using namespace std;


typedef string::const_iterator StrIter;

class Node;

class Node {
  public:
  char value;
  vector<Node> children;


  void addWord(StrIter begin, StrIter end) {
    if(end - begin < 1)
      return;
    char character = *begin;
    for(int i=0; i!=children.size(); i++) {
      if(children[i].value == character) {
        children[i].addWord(begin+1, end);
        return;
      }
    }
    Node node;
    node.value = character;
    node.addWord(begin+1, end);
    children.push_back(node);
  }

  void addWord(string &word) {
    addWord(word.begin(), word.end());
  };


  bool findWord(StrIter begin, StrIter end) {
    char character = *begin;
    for(int i=0; i!=children.size(); i++)
      if(children[i].value == character) {
        if(end-begin == 1)
          return true;
        return findWord(begin+1, end);
      }
    return false;
  };

  bool findWord(string &word) {
    return findWord(word.begin(), word.end());
  };

  bool findWord(string word) {
    return findWord(word.begin(), word.end());
  }

  bool findWord(const char* word) {
    return findWord(string(word));
  };

};

string reverse(string &word) {
  string result;
  for(string::reverse_iterator character = word.rbegin(); character != word.rend(); character++) {
    result.push_back(*character);
  }
  return result;
};

using namespace std;

int main(void) {
  string word = "abccba";
  cout << word << endl;
  Node root;
  for(StrIter character = word.begin(); character != word.end()-3; character++) {
    root.addWord(character, character+3);
  }

  string reversed = reverse(word); 
  for(StrIter character = reversed.begin(); character != reversed.end()-3; character++) {
    if(root.findWord(character, character+3)) {
      cout << reversed.substr((character - reversed.begin()), 3) << endl;
    }
  }
  return 0;
}
