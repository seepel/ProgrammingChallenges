#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<string> interleave(string word1, string word2) {
  vector<string> result;
  if(word1.size() == 0) {
    result.push_back(word2);
  } else if(word2.size() == 0) {
    result.push_back(word1);
  } else {
    for(int i=0; i<= word1.size(); i++) {
      cout << i << endl;
      char c = word2[0];
      string left = word1.substr(0, i);
      string right = word1.substr(i, word1.size()-i);
      vector<string> interleaved = interleave(right, word2.substr(1,word2.size()-1));
      for(int j=0; j!= interleaved.size(); j++) {
        result.push_back(left + c + interleaved[j]);
      }
    }
  }
  return result;
}

int main(void) {
  string word1 = "abc";
  string word2 = "123";

  vector<string> interleaved = interleave(word1, word2);
  for(int i=0; i!=interleaved.size(); i++)
    cout << interleaved[i] << endl;

  return 0;
}
