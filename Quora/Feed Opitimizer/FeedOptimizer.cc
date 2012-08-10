#include <string>
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <stdint.h>

using namespace std;

struct Story {
  uint64_t id;
  uint64_t time;
  uint64_t score;
  uint64_t height;
};

bool operator== (const Story& story1, const Story& story2) { return story1.id  == story2.id; }
bool operator!= (const Story& story1, const Story& story2) { return !(story1  == story2); }
bool operator< (const Story& story1, const Story& story2) { return story1.id  < story2.id; }

struct Refresh {
  uint64_t time;
};

enum {
  STORY,
  REFRESH,
  ERROR
};



void parse();
uint64_t parseType();
Story parseStory(uint64_t id);
void addScore(Story &story);
Refresh parseRefresh();
void packStories();

deque<Story> stories_;
uint64_t timeWindow_;
bool didPop_;
uint64_t height_;

void parse() {
  uint64_t numberOfEvents;
  cin >> numberOfEvents;
  cin >> timeWindow_;
  cin >> height_;
  uint64_t id = 0;
  didPop_ = false;
  for(uint64_t i=0; i != numberOfEvents; i++) {
    uint64_t type = parseType();
    uint64_t score = 0;
    switch(type) {
      case STORY:
        stories_.push_back(parseStory(++id));
        if(!didPop_) addScore(stories_[stories_.size()-1]);
        break;
      case REFRESH:
        parseRefresh();
        packStories();
        break;
      case ERROR:
        break;
    }
  }
};

uint64_t parseType() {
  string type;
  cin >> type;
  if(type == "S") {
    return STORY;
  } else if(type == "R") {
    return REFRESH;
  }
  return ERROR;
}

vector<vector<uint64_t> > totalScores_;
vector<vector<uint64_t> > totalIds_;

void addScore(Story &story) {
  uint64_t next = totalScores_.size();
  vector<uint64_t> nextRow;
  totalScores_.push_back(nextRow);
  vector<uint64_t> nextIds;
  totalIds_.push_back(nextIds);
  for(uint64_t h=0; h<=height_; h++) {
    uint64_t id = 0;
    if(h >= story.height) {
      if(next == 0) {
        totalScores_[next].push_back(story.score);
        id = story.id;
      } else {
        totalScores_[next].push_back(max(totalScores_[next-1][h], totalScores_[next-1][h-story.height] + story.score));
        if(totalScores_[next][h] > totalScores_[next-1][h])
          id = story.id;
      }
    } else {
      if(next == 0) {
        totalScores_[next].push_back(0);
      } else {
        totalScores_[next].push_back(totalScores_[next-1][h]);
      }
    }
    totalIds_[next].push_back(id);
  }
}

Story parseStory(uint64_t id) {
  Story story;
  story.id = id;
  uint64_t time;
  uint64_t score;
  uint64_t height;
  cin >> story.time;
  cin >> story.score;
  cin >> story.height;
  return story;
}

Refresh parseRefresh() {
  Refresh refresh;
  cin >> refresh.time;
  while(refresh.time - stories_.front().time > timeWindow_) {
    stories_.pop_front();
    didPop_ = true;;
  }
  return refresh;
}

void printItems(vector<vector<uint64_t> > &ids, int64_t row, int64_t col) {
  if(row < 0 || col < 0) return;
  uint64_t id = totalIds_[row][col];
  if(id == 0) {
    row--;
  } else {
    col -= stories_[row].height;
    row--;
  }
  printItems(ids, row, col);
  if(id != 0) {
    cout << id << " ";
  }
};

void packStories() {
  // rebuild the matrix if we've removed elements and the new maximum is larger
  // OR if the current list has lost an element
  //if((didPop_ && (totalScores_[totalScores_.size()-1][height_] != totalScores_[totalScores_.size()-2][height_])) || didPopBig_) {
  if(didPop_) {
    totalScores_.clear();
    totalIds_.clear();
    for(uint64_t s=0; s!=stories_.size(); s++) {
      addScore(stories_[s]);
    }
    didPop_ = false;
  }
  cout << totalScores_[stories_.size()-1][height_] << " ";
  bool keepGoing = true;
  uint64_t row = totalScores_.size()-1;
  uint64_t col = totalScores_[totalScores_.size()-1].size()-1;
  printItems(totalIds_, row, col);

  cout << endl;
};

int main(int argc, const char* argv[]) {
  parse();
}
