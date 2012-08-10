#include <string>
#include <iostream>
#include <map>

using namespace std;

map<int, string> words;

string knownWord() {
  return words[rand()%words.size()];
}

string newWord(int data, int wordLength) {
  string word;
  int length = rand()%wordLength;
  for(int i=0; i!= length; i++) {
    char c = (char)(rand() % 26) + 'a';
    c = 'a';
    word.push_back(c);
  }
  words[words.size()] = word;
  return word;
}

void printWord(int data, int wordlength) {
  string word;
  while(word.size() < data) {
    string nextWord;
    if(rand()%100 != 0 && words.size() > 20) {
      nextWord = knownWord();
    } else {
      nextWord = newWord(data, wordlength);
    }
    if(word.size() + nextWord.size() + 1 > data)
      break;
    if(nextWord.size() > 0) {
      if(word.size() > 0)
        word += " ";
      word += nextWord;
    }
  }
  cout << word;
  cout << endl;
};

int main(void) {
  int adds = 40000;
  int dels = 10000;
  int queries = 20000;
  int wqueries = 1000;
  int boosts = 25;
  int data = 98;
  int query = 50;
  int word = 10;

  /*
  adds = 10;
  dels = 10;
  queries = 10;
  wqueries = 10;
  boosts = 10;
  data = 10;
  */
  cout << adds + dels + queries + wqueries << endl;
  for(int i=1; i!=1+adds; i++) {
    cout << "ADD user u" << i << " 1.0 ";
    printWord(data, word);
  }
  for(int i=0; i!=queries; i++) {
    cout << "QUERY 20 ";
    printWord(query, word);
  }
  for(int i=0; i!=wqueries; i++) {
    cout << "QUERY 20 " << boosts << " ";
    for(int j=0; j!=boosts; j++) {
      cout << "user:2 "; 
    }
    printWord(query, word);
  }
  for(int i=0; i!=dels; i++) {
    cout << "DEL u" << i << endl;;
  }
  return 0;
}
