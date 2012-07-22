#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<const string, vector<string> > memoized;


vector<string> segmentString(const string &input, vector<string> &dictionary, bool memoize) {
  vector<string> output;
  if(memoized.find(input) != memoized.end() && memoize) {
    return memoized[input];
  }
  for(int i=0; i <= input.size(); i++)  {
    if(find(dictionary.begin(), dictionary.end(), input.substr(0,i)) != dictionary.end()) {
      output = segmentString(input.substr(i,input.size()-i), dictionary, memoize);
      if(output.size() > 0 || i == input.size()) {
	output.insert(output.begin(), input.substr(0,i));
	break;
      }
    }
  }
  memoized[input] = output;
  return output;
}

int main(int argc, char **argv) {
  bool memoize = false;
  bool pathological = false;
  for(int i=1; i!=argc; i++) {
    if(strcmp(argv[i], "memoize") == 0) {
      cout << "Using memoization" << endl;
      memoize = true;
    }
    if(strcmp(argv[i], "pathological") == 0) {
      cout << "Making pathological" << endl;
      pathological = true;
    }
  }
  vector<string> dictionary;
  if(pathological) {
    string astring = "a";
    for(int i=0; i != 100; i++) {
      dictionary.push_back(astring);
      astring.append("a");
    }
  }
  dictionary.push_back("apple");
  dictionary.push_back("apple");
  dictionary.push_back("applepicker");
  dictionary.push_back("pie");
  dictionary.push_back("test");
  dictionary.push_back("foo");
  dictionary.push_back("bar");
  dictionary.push_back("baz");
  string input = "applepickerpie";
  if(pathological) {
    for(int i=0; i!= 100; i++) {
      input.append("a");
    }
    input.append("b");
  }
  vector<string> output = segmentString(input, dictionary, memoize);

  for(vector<string>::const_iterator str = output.begin(); str != output.end(); str++) {
    cout << *str << " ";
  }
  cout << endl;
  return 0;
}
