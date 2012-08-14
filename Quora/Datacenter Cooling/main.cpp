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

int degree(vector<vector<int> > &rooms, int row, int col) {
  int degree = 0;
  if(row > 0) if(rooms[row-1][col] == 0) degree++;
  if(row < rooms.size()-1) if(rooms[row+1][col] == 0) degree++;
  if(col  > 0) if(rooms[row][col-1] == 0) degree++;
  if(col < rooms[row].size()-1) if(rooms[row][col+1] == 0) degree++;
  return degree;
}

int count(vector<vector<int> > &rooms, int row, int col, int endrow, int endcol) {
  if(row >= rooms.size()) return 0;
  if(row < 0) return 0;
  if(col >= rooms[row].size()) return 0;
  if(col < 0) return 0;
  if(rooms[row][col] == END) {
    for(int i=0; i!=rooms.size(); i++) {
      for(int j=0; j!=rooms[i].size(); j++) {
        if(rooms[i][j] == 0)
          return 0;
      }
    }
    return 1;
  }
  if(rooms[row][col] != OWNED) return 0;
  if(degree(rooms, endrow, endcol) == 0) {
    return 0;
  }
  rooms[row][col] = VISITED;
  int sum = 0;
  sum += count(rooms, row+1, col, endrow, endcol);
  sum += count(rooms, row-1, col, endrow, endcol);
  sum += count(rooms, row, col+1, endrow, endcol);
  sum += count(rooms, row, col-1, endrow, endcol);
  rooms[row][col] = OWNED;
  return sum;
}

int main(void) {
  int width, height;
  cin >> width;
  cin >> height;
  int value;
  vector<vector<int> > matrix;
  int row = 0;
  int col = 0;
  int endrow = 0;
  int endcol = 0;
  for(int i=0; i!=height; i++) {
    vector<int> nextRow;
    for(int j=0; j!=width; j++) {
      cin >> value;
      nextRow.push_back(value);
      if(value == 2) {
        row = i;
        col = j;
      }
      if(value == 3) {
        endrow = i;
        endcol = j;
      }
    }
    matrix.push_back(nextRow);
  }
  matrix[row][col] = OWNED;
  cout << count(matrix, row, col, endrow, endcol) << endl;
  return 0;
}
