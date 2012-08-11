#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

struct Story {
  int id;
  int time;
  int score;
  int height;
};

bool operator== (const Story& story1, const Story& story2) { return story1.id  == story2.id; }
bool operator!= (const Story& story1, const Story& story2) { return !(story1  == story2); }
bool operator< (const Story& story1, const Story& story2) { return story1.id  < story2.id; }

struct Refresh {
  int time;
  vector<Story> stories;
};

enum {
  STORY,
  REFRESH,
  ERROR
};

void parse();
int parseType();
Story parseStory(int id);
void printRefresh(Refresh refresh, int height);
int scoreForStories(vector<Story> stories);
Refresh parseRefresh(vector<Story> stories, int timeWindow);
vector<Story> parseStoriesForRefresh(vector<Story> stories, int time);
vector<Story> packStories(vector<Story> stories, int height);

void parse() {
  int numberOfEvents;
  int timeWindow;
  int height;
  cin >> numberOfEvents;
  cin >> timeWindow;
  cin >> height;
  vector<Story> stories;
  int id = 0;
  for(int i=0; i != numberOfEvents; i++) {
    int type = parseType();
    switch(type) {
      case STORY:
	stories.push_back(parseStory(++id));
	break;
      case REFRESH:
	printRefresh(parseRefresh(stories, timeWindow), height);
	break;
      case ERROR:
	break;
    }
  }
};

int parseType() {
  string type;
  cin >> type;
  if(type == "S") {
    return STORY;
  } else if(type == "R") {
    return REFRESH;
  }
  return ERROR;
}

Story parseStory(int id) {
  Story story;
  story.id = id;
  int time;
  int score;
  int height;
  cin >> story.time;
  cin >> story.score;
  cin >> story.height;
  return story;
}

Refresh parseRefresh(vector<Story> stories, int timeWindow) {
  Refresh refresh;
  cin >> refresh.time;
  refresh.stories = parseStoriesForRefresh(stories, refresh.time - timeWindow);
  return refresh;
}

vector<Story> parseStoriesForRefresh(vector<Story> stories, int time) {
  vector<Story> storiesForRefresh;
  for(vector<Story>::reverse_iterator story = stories.rbegin(); story != stories.rend(); story++) {
    if(story->time < time)
      break;
    storiesForRefresh.push_back(*story);
  }
  return storiesForRefresh;
}

void printRefresh(Refresh refresh, int height) {
  vector<Story> stories = packStories(refresh.stories, height);
  int score = 0;
  for(vector<Story>::iterator story = stories.begin(); story != stories.end(); story++)
    score += story->score;
  cout << score << " " << stories.size();
  for(vector<Story>::iterator story = stories.begin(); story != stories.end(); story++)
    cout << " " << story->id;
  cout << endl;
}

int scoreForStories(vector<Story> stories) {
  int score = 0;
  for(vector<Story>::iterator story = stories.begin(); story != stories.end(); story++) {
    score += story->score;
  }
  return score;
}

bool sortStoriesByDensity(Story story1, Story story2) {
  return (float)story1.score/(float)story1.height <= (float)story2.score/(float)story2.height;
}

bool sortStoriesById(Story story1, Story story2) {
  return story1.id < story2.id;
}

template<class T>
bool compareSize(vector<T> set1, vector<T> set2) {
  if(set1.size() != set2.size())
    return set1.size() < set2.size();
  for(int i=0; i != set1.size(); i++) {
    if(set1[i] != set2[i])
      return set1[i] < set2[i];
  }
  return false;
}

vector<Story> packStories(vector<Story> stories, int height) {
  vector<Story> packedStories;
  vector<int> heights;
  vector<int> scores;
  vector<vector<int> > m;
  scores.push_back(0);
  heights.push_back(height+1);
  for(vector<Story>::iterator story = stories.begin(); story != stories.end(); story++) {
    heights.push_back(story->height);
    scores.push_back(story->score);
  }
  map<int, map<int, vector<Story> > > sets;
  map<int, map<int, int> > totalScores;
  for(int i=0; i!=scores.size(); i++) {
    for(int h=0; h<=height; h++) {
      if(i == 0 || h == 0) {
	vector<Story> set;
	sets[i][h] = set;
	totalScores[i][h] = 0;
      } else if(heights[i] > h) {
	vector<Story> set(sets[i-1][h]);
	sets[i][h] = set;
	totalScores[i][h] = totalScores[i-1][h];
      } else {
	if(totalScores[i-1][h] < totalScores[i-1][h - heights[i]] + scores[i]) {
	  vector<Story> set(sets[i-1][h - heights[i]]);
	  set.push_back(stories[i-1]);
	  sets[i][h] = set;
	  totalScores[i][h] = totalScores[i-1][h - heights[i]] + scores[i];
	} else {
	  vector<Story> set(sets[i-1][h]);
	  sets[i][h] = set;
	  totalScores[i][h] = totalScores[i-1][h];
	}
      }
      sort(sets[i][h].begin(), sets[i][h].end());
    }
  }
  int maxScore = 0;
  vector<vector<Story> > maxSets;
  for(int i=0; i!=scores.size(); i++) {
    for(int h=0; h<=height; h++) {
      if(totalScores[i][h] >= maxScore) {
	if(totalScores[i][h] > maxScore)
	  maxSets.clear();
	maxScore = totalScores[i][h];
	if(find(maxSets.begin(), maxSets.end(), sets[i][h]) == maxSets.end())
	  maxSets.push_back(sets[i][h]);
      }
    }
  }
  sort(maxSets.begin(), maxSets.end(), compareSize<Story>);
  packedStories = maxSets[0];
  return packedStories;
}

vector<Story> packStoriesByGreedy(vector<Story> stories, int height) {
  vector<Story> packedStories;
  sort(stories.begin(), stories.end(), sortStoriesByDensity);
  int heightSoFar = 0;
  for(vector<Story>::iterator story = stories.begin(); story != stories.end(); story++) {
    if(story->height + heightSoFar > height)
      continue;
    heightSoFar += story->height;
    packedStories.push_back(*story);
  }
  sort(packedStories.begin(), packedStories.end(), sortStoriesById);
  return packedStories;
}

int main(int argc, const char* argv[]) {
  parse();
}
