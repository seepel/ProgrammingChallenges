#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <limits.h>

using namespace std;

vector<string> split(const string text, char delimeter) {
  vector<string> result;
  stringstream stream(text);
  string word;
  while(getline(stream, word, delimeter)) {
    result.push_back(word);
  }
  return result;
};

typedef enum  {
  UNDEFINED = 0,
  USER,
  TOPIC,
  QUESTION,
  BOARD
} QueryType;

class Boost {
  public:
    Boost() { type = UNDEFINED; id = ""; }
  QueryType type;
  string id;
  float value;
};

class QueryResult {
  public:
    QueryType type;
    string id;
    float score;
    int time;

    QueryResult  boost(vector<Boost> &boosts) const {
      QueryResult result;
      result.type = this->type;
      result.id = this->id;
      result.score = this->score;
      result.time = this->time;
      for(vector<Boost>::const_iterator boost = boosts.begin(); boost != boosts.end(); boost++) {
        if(boost->type == type) result.score *= boost->value;
        if(boost->id == id) result.score *= boost->value;
      }
      return result;
    };
};

class QueryResultCompare {
  public:
  bool operator()(const QueryResult &left, const QueryResult &right) {
    /*
    if(left.score < right.score) return true;
    if(left.score == right.score && left.id < right.id) return true;
    return false;
    */
    return left.id < right.id;
  };
};

class QueryResultPrioritize {
  public:
  bool operator()(const QueryResult &left, const QueryResult &right) {
    if(left.score < right.score) return true;
    if(left.score == right.score && left.time < right.time) return true;
    return false;
  };
};

QueryResult parseQueryResultAdd(int time) {
  QueryResult result;
  result.time = time;
  string type;
  cin >> type;
  if(type == "topic") {
    result.type = TOPIC;
  } else if(type == "user") {
    result.type = USER;
  } else if(type == "question") {
    result.type = QUESTION;
  } else if(type == "board") {
    result.type = BOARD;
  }  
  cin >> result.id;
  cin >> result.score;
  return result;
};

QueryResult parseQueryResultDel() {
  QueryResult result;
  cin >> result.id;
  return result;
};

string parseDataString() {
  char data[100];
  cin.getline(data,100);
  return string(data);
};

class Query {
  public:
  int numberOfResults;
  string data;
  vector<Boost> boosts;
};

Query parseQuery() {
  Query query;
  cin >> query.numberOfResults;
  query.data = parseDataString();
  return query;
};

Boost parseBoost() {
  Boost boost;
  string boostString;
  cin >> boostString;
  vector<string> boostComponents = split(boostString, ':');
  if(boostComponents[0] == "topic") {
    boost.type = TOPIC;
  } else if(boostComponents[0] == "user") {
    boost.type = USER;
  } else if(boostComponents[0] == "question") {
    boost.type = QUESTION;
  } else if(boostComponents[0] == "board") {
    boost.type = BOARD;
  } else {
    boost.id = boostComponents[0];
  }

  boost.value = atof(boostComponents[1].c_str());

  return boost;
};

Query parseWQuery() {
  Query query;
  cin >> query.numberOfResults;
  int numberOfBoosts = 0;
  cin >> numberOfBoosts;
  for(int i=0; i!=numberOfBoosts; i++) {
    query.boosts.push_back(parseBoost());
  }
  query.data = parseDataString();
  return query;
};

typedef set<QueryResult, QueryResultPrioritize> QuerySet;
typedef set<QueryResult, QueryResultPrioritize> QueryPrioritizedSet;
typedef string::const_iterator StrItr;

class Leaf {
  public:
  QuerySet queryResults;
  map<char, Leaf*> children;

  void append(QueryResult &result, StrItr begin, StrItr end) {
    Leaf *leaf = NULL;
    if(children.find(*begin) == children.end()) {
      leaf = new Leaf();
      children[*begin] = leaf;
    } else {
      leaf = children[*begin];
    }
    leaf->queryResults.insert(result);
    if(end-begin > 1)
      leaf->append(result, begin+1, end);
  };

  void remove(QueryResult &result) {
    for(map<char, Leaf*>::const_iterator leaf = children.begin(); leaf != children.end(); leaf++) {
      QuerySet::iterator it = leaf->second->queryResults.find(result);
      if(it == leaf->second->queryResults.end())
        continue;
      leaf->second->queryResults.erase(it);
      leaf->second->remove(result);
    }
  };

  Leaf *find(StrItr begin, StrItr end) {
    if(children.find(*begin) == children.end()) { return NULL; }
    Leaf *leaf = children[*begin];
    if(end-begin == 1) {
      return leaf;
    }
    return leaf->find(begin+1, end);
  };

};


bool sortLeafs(Leaf *left, Leaf *right) {
  return left->queryResults.size() < right->queryResults.size();
};

class Tree {
  public:
    Leaf root;

    void insert(QueryResult &result, string &text) { 
      transform(text.begin(), text.end(), text.begin(), ::tolower);
      root.append(result, text.begin(), text.end()); 
    };

    void remove(QueryResult &result) { root.remove(result); }

    QuerySet find(vector<string> &tokens, vector<Boost> &boosts, int max = 20) {
      QuerySet result;
      vector<Leaf *> leafs;
      for(vector<string>::iterator token = tokens.begin(); token != tokens.end(); token++) {
        transform(token->begin(), token->end(), token->begin(), ::tolower);
        Leaf *leaf = NULL;
        leaf = root.find(token->begin(), token->end()); 
        if(leaf == NULL)
          return result;
        leafs.push_back(leaf);
      }

      if(leafs.size() == 0) return result;
      sort(leafs.begin(), leafs.end(), sortLeafs);
      for(QuerySet::reverse_iterator queryResult = leafs[0]->queryResults.rbegin(); queryResult != leafs[0]->queryResults.rend(); queryResult++) {
        bool inAll = true;
        for(int i=1; i!=leafs.size(); i++) {
          if(leafs[i]->queryResults.find(*queryResult) == leafs[i]->queryResults.end()) {
            inAll = false;
            break;
          }
        }
        if(inAll)
          result.insert(queryResult->boost(boosts));
        if(boosts.size() == 0 && result.size() == max)
          return result;
      }
      return result;
    };

    QuerySet find(vector<string> &tokens, int max = 20) {
      vector<Boost> boosts;
      return find(tokens, boosts, max);
    };

    QuerySet find(const string &token, vector<Boost> &boosts, int max = 20) {
      vector<string> tokens;
      tokens.push_back(token);
      return find(tokens, boosts, max);
    };

    QuerySet find(const string &token, int max = 20) {
      vector<Boost> boosts;
      return find(token, boosts, max);
    };

};

void printQueryResults(QueryPrioritizedSet &queryResults, int max) {
  int i = 0;
  for(QueryPrioritizedSet::reverse_iterator queryResult = queryResults.rbegin(); queryResult != queryResults.rend(); queryResult++) {
    if(i >= max) break;
    cout << queryResult->id << " ";
    i++;
  }
  cout << endl;
};

//#define PARSE_ONLY

int main(void) {
  int lines;
  cin >> lines;
  Tree tree;
  int time = 0;
  for(int i=0; i!=lines; i++) {
    string type;
    cin >> type;
    if(type == "ADD") {
      QueryResult query = parseQueryResultAdd(time);
      time++;
      string dataString = parseDataString();
#ifndef PARSE_ONLY
      dataString = dataString.substr(1,dataString.size()-1);
      vector<string> tokens = split(dataString, ' ');
      for(int i=0; i!=tokens.size(); i++) {
        tree.insert(query, tokens[i]);
      }
#endif
    } else if(type == "DEL") {
      QueryResult query = parseQueryResultDel();
#ifndef PARSE_ONLY
      tree.remove(query);
#endif
    } else if(type == "QUERY") {
      Query query = parseQuery();
#ifndef PARSE_ONLY
      vector<string> words = split(query.data.substr(1,query.data.size()-1), ' ');
      QuerySet querySet = tree.find(words, query.numberOfResults);
      printQueryResults(querySet, query.numberOfResults);
#endif
     } else if(type == "WQUERY") {
      Query query = parseWQuery();
#ifndef PARSE_ONLY
      vector<string> words = split(query.data.substr(1,query.data.size()-1), ' ');
      QuerySet querySet = tree.find(words, query.boosts, query.numberOfResults);
      printQueryResults(querySet, query.numberOfResults);
#endif
    }
  }
  return 0;
}
