#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <assert.h>

#define DEBUG

using namespace std;

struct Position {
  double x;
  double y;
  Position() { }
  Position(double xPosition, double yPosition) : x(xPosition), y(yPosition) { }
};

enum {
  TOPIC,
  QUESTION
};

struct Entity {
  int id;
  Position position;
  int type;
};

bool operator== (const Entity &entity1, const Entity &entity2) { return entity1.id == entity2.id; }
bool operator!= (const Entity &entity1, const Entity &entity2) { return !(entity1.id == entity2.id); }
bool operator< (const Entity &entity1, const Entity &entity2) { return entity1.id < entity2.id; }

Entity parseTopic() {
  Entity topic;
  topic.type = TOPIC;
  cin >> topic.id;
  cin >> topic.position.x;
  cin >> topic.position.y;
#ifdef DEBUG
  cout << "topic: " << topic.id << " " << topic.position.x << " " << topic.position.y << endl;
#endif
  return topic;
};

vector<Entity> parseQuestion(vector<Entity> &topics) {
  vector<Entity> questions;
  int id;
  cin >> id;
  int numberOfTopics = 0;
  cin >> numberOfTopics;
  for(int i=0; i!=numberOfTopics; i++) {
    int topicID;
    cin >> topicID;
    for(vector<Entity>::iterator topic = topics.begin(); topic != topics.end(); topic++) {
      if(topic->id != topicID)
	continue;
      Entity question;
      question.id = id;
      question.position = topic->position;
      question.type = QUESTION;
      questions.push_back(question);
#ifdef DEBUG
      cout << "question: " << question.id << " " << question.position.x << " " << question.position.y << endl;
#endif
    }
  }
  return questions;
}

struct Query {
  int type;
  int numberOfResults;
  Position position;
};

Query parseQuery() {
  Query query;
  string type;
  cin >> type;
  if(type == "t")
    query.type = TOPIC;
  else if(type == "q")
    query.type = QUESTION;
  else
    query.type = -1;
  cin >> query.numberOfResults;
  cin >> query.position.x;
  cin >> query.position.y;
#ifdef DEBUG
  cout << "query: " << query.type 
       << " " << query.numberOfResults 
       << " " << query.position.x 
       << " " << query.position.y << endl;
#endif
  return query;
}

enum {
  XAXIS,
  YAXIS
};

bool compareEntitiesByX(const Entity &entity1, const Entity &entity2) {
  return entity1.position.x < entity2.position.x;
}

bool compareEntitiesByY(const Entity &entity1, const Entity &entity2) {
  return entity1.position.y < entity2.position.y;
}

void sortEntitiesByAxis(vector<Entity>::iterator entityBegin, vector<Entity>::iterator entityEnd, int axis) {
  switch(axis) {
    case XAXIS:
      sort(entityBegin, entityEnd, compareEntitiesByX);
      break;
    case YAXIS:
      sort(entityBegin, entityEnd, compareEntitiesByY);
      break;
  }
}

double valueForEntity(vector<Entity>::iterator entity, int axis) {
  switch(axis) {
    case XAXIS:
      return entity->position.x;
      break;
    case YAXIS:
      return entity->position.y;
      break;
    default:
      return 0;
  }
}

vector<Entity>::iterator findMedian(vector<Entity>::iterator entityBegin, vector<Entity>::iterator entityEnd, int axis) {
    vector<Entity>::iterator median = entityEnd - (entityEnd - entityBegin)/2-1;
    vector<Entity>::iterator medianleft = median - 1;
    while(valueForEntity(median, axis) == valueForEntity(medianleft, axis)) {
      median -= 1;
      medianleft -=1;
      if(median == entityBegin)
	break;
    }
    return median;
}

struct Node {
  Position position;
  Entity entity;
  Node *left;
  Node *right;
  int axis;

  Node(vector<Entity> entities, int depth = 0) : left(NULL), right(NULL) {
    axis = depth % 2;
    sortEntitiesByAxis(entities.begin(), entities.end(), axis);
    vector<Entity>::iterator median = findMedian(entities.begin(), entities.end(), axis);
    entity = *median;
    position = median->position;
    if(entities.size() == 1)
      return;
    if(median - entities.begin() > 0) {
      vector<Entity> leftEntities(entities.begin(), median);
      left = new Node(leftEntities, depth+1);
    }
    if(entities.end() - median - 1 > 0) {
      vector<Entity> rightEntities(median + 1, entities.end());
      right = new Node(rightEntities, depth+1);
    }
  }

  ~Node() {
    /*
    if(left != NULL)
      delete left;
    if(right != NULL)
      delete right;
      */
  }

  bool query(vector<Node> &nodes, Position &queryPosition, int numberOfNeighbors, int type) {
#ifdef DEBUG
    cout << "in: " << position.x << " " << position.y << " " << nodes.size() << " " << entity.id << endl;
#endif
    // Closest Leaf keep searching
    if(left == NULL && right == NULL && nodes.size() == 0)  {
      if(entity.type == type) 
	nodes.push_back(*this);
      return true;
    }

    Node *nearSide = NULL;
    Node *farSide = NULL;
    switch(axis) {
      case XAXIS:
	if(queryPosition.x < position.x) {
	  nearSide = left;
	  farSide = right;
	} else {
	  nearSide = right;
	  farSide = left;
	}
	break;
      case YAXIS:
	if(queryPosition.y < position.y) {
	  nearSide = left;
	  farSide = right;
	} else {
	  nearSide = right;
	  farSide = left;
	}
	break;
    }


    //Loop through near side first
    bool checkFarSide = true;
    if(nearSide != NULL)
      checkFarSide = nearSide->query(nodes, queryPosition, numberOfNeighbors, type);
    if(checkFarSide && farSide == NULL)
      checkFarSide = false;
#ifdef DEBUG
    cout << "out: " << position.x << " " << position.y << " " << nodes.size() << " " << entity.id << " out" << endl;
#endif
    double distance = pow(position.x - queryPosition.x, 2) + pow(position.y - queryPosition.y, 2);
    // If the current node is less than the furthest distance insert the current node keeping ascending order
    Node furthestNode = nodes[nodes.size()-1];
    double furthestDistance = pow(queryPosition.x - furthestNode.position.x, 2) + pow(queryPosition.y - furthestNode.position.y, 2);
    if(distance <= furthestDistance || nodes.size() < numberOfNeighbors) {
      vector<Node>::iterator insertionNode = nodes.end();
      for(vector<Node>::iterator node = nodes.begin(); node != nodes.end(); node++) {
	if(node->entity.type != type || node->entity.id == entity.id)
	  continue;
	double nodeDistance = pow(node->position.x - queryPosition.x, 2) + pow(node->position.y - queryPosition.y, 2);
	if(distance <= nodeDistance)
	  insertionNode = node;
	else
	  break;
      }
      nodes.insert(insertionNode, *this);
      /*
      while(nodes.size() > numberOfNeighbors)
	nodes.pop_back();
	*/
    }


    // reset the furthest node in case it is this one
    furthestNode = nodes[nodes.size()-1];
    furthestDistance = pow(queryPosition.x - furthestNode.position.x, 2) + pow(queryPosition.y - furthestNode.position.y, 2);
    //If the furthest distance crosses the plane check other side
    if(!checkFarSide)
      return false;

    switch(axis) {
      case XAXIS:
	if(furthestDistance > position.x) {
	  farSide->query(nodes, queryPosition, numberOfNeighbors, type);
	  return true;
	} else {
	  return false;
	}
	break;
      case YAXIS:
	if(furthestDistance > position.y) {
	  farSide->query(nodes, queryPosition, numberOfNeighbors, type);
	  return true;
	} else {
	  return false;
	}
	break;
    }
    // Should never get here but lets just kill it
    cout << "Failed to determine next step in tree" << endl;
    assert(false);
  }
};

template<class T>
vector<T> parseObjects(int numberOfObjects, T (*parseFunction)());

vector<Entity> parseQuestions(int numberOfQuestions, vector<Entity> &topics);

bool sortReverse(int n, int m) { return n > m; }

int main(int argc, const char* argv[]) {

  int numberOfTopics;
  int numberOfQuestions;
  int numberOfQueries;
  cin >> numberOfTopics;
  cin >> numberOfQuestions;
  cin >> numberOfQueries;
#ifdef DEBUG
  cout << "numbers: " << numberOfTopics << " " << numberOfQuestions << " " << numberOfQueries << endl;
#endif
  vector<Entity> topics = parseObjects(numberOfTopics, parseTopic);
  vector<Entity> questions = parseQuestions(numberOfQuestions, topics);
  vector<Query> queries = parseObjects(numberOfQueries, parseQuery);
  Node tree = Node(topics);
//  for(vector<Query>::iterator query = queries.begin(); query != queries.end(); query++) {
  for(vector<Query>::iterator query = queries.begin(); query != queries.end(); query++) {
    vector<Node> nodes;
    tree.query(nodes, query->position, query->numberOfResults, query->type);
    for(vector<Node>::iterator node = nodes.begin(); node != nodes.end(); node++)
      if(query->type == TOPIC) {
	cout << node->entity.id << " ";
      }/* else if(query->type == QUESTION) {
	sort(node->topic.questions.begin(), node->topic.questions.end(), sortReverse);
	for(vector<int>::iterator question = node->topic.questions.begin(); question != node->topic.questions.end(); question++) {
	  if(find(questionsDisplayed.begin(), questionsDisplayed.end(), *question) != questionsDisplayed.end())
	    continue;
	  cout << *question << " ";
	  questionsDisplayed.push_back(*question);
	}
      }
    */
    cout << endl;
    
    break;
  }
  cout << "done" << endl;
}


template<class T>
vector<T> parseObjects(int numberOfObjects, T (*parseFunction)()) {
  vector<T> objects;
  for(int i=0; i!=numberOfObjects; i++)
    objects.push_back((*parseFunction)());
  return objects;
}

vector<Entity> parseQuestions(int numberOfQuestions, vector<Entity> &topics) {
  vector<Entity> questions;
  for(int i=0; i!=numberOfQuestions; i++) {
    vector<Entity> newQuestions = parseQuestion(topics);
    questions.insert(questions.end(), newQuestions.begin(), newQuestions.end());
  }
  return questions;
}
