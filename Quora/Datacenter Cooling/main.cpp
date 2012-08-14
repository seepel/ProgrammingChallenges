#include <iostream>
#include <vector>

using namespace std;

struct Room;

enum {
  OWNED = 0,
  NOT_OWNED = 1,
  START = 2,
  END = 3,
  VISITED = 4
};

struct Room;

struct Room {
  int type;
  bool visited;
  vector<Room *> rooms;
};

int total = 0;
int visited = 0;
vector<vector<Room *> > matrix;

void visit(Room *room) {
  room->visited = true;
  visited++;
}

void unvisit(Room *room) {
  room->visited = false;
  visited--;
};

vector<Room *> roomsToUnvisit;

bool connected(Room *room, bool doUnvisit = true) {
  visit(room);
  bool isConnected = false;
  if(visited == total) isConnected = true;
  roomsToUnvisit.push_back(room);
  for(int i=0; i!=room->rooms.size(); i++) {
    if(isConnected) break;
    if(!room->rooms[i]->visited) isConnected = connected(room->rooms[i], false);
  }
  if(doUnvisit) {
    for(int i=0; i!=roomsToUnvisit.size(); i++) {
      unvisit(roomsToUnvisit[i]);
    }
    roomsToUnvisit.clear();
  }
  return isConnected;
};

int count(Room *room) {
  int sum = 0;
  if(!connected(room)) {  return 0; }
  visit(room);
  if(room->type == END && visited == total) sum = 1;
  for(int i=0; i!=room->rooms.size(); i++) {
    if(!room->rooms[i]->visited) sum += count(room->rooms[i]);
  }
  unvisit(room);
  return sum;
};

int main(void) {
  int width, height;
  cin >> width;
  cin >> height;
  int value;
  int row = 0;
  int col = 0;
  int endrow = 0;
  int endcol = 0;
  Room *start = NULL;
  for(int i=0; i!=height; i++) {
    vector<Room *> nextRow;
    for(int j=0; j!=width; j++) {
      cin >> value;
      if(value == 1) { nextRow.push_back(NULL); continue; }
      Room *room = new Room();
      room->type = value;
      room->visited = false;
      total++;
      if(i > 0) {
        if(matrix[i-1][j] != NULL) {
          room->rooms.push_back(matrix[i-1][j]);
          matrix[i-1][j]->rooms.push_back(room);
        }
      }
      if(j > 0) {
        if(nextRow[j-1] != NULL) {
          room->rooms.push_back(nextRow[j-1]);
          nextRow[j-1]->rooms.push_back(room);
        }
      }
      if(room->type == START) start = room;
      nextRow.push_back(room);
    }
    matrix.push_back(nextRow);
  }
  cout << count(start) << endl;
  return 0;
}
