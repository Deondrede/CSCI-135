#include <climits>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

bool fenceE = false;
bool fenceW = false;
bool fenceN = false;
bool fenceS = false;

int fences = 0;

int ROWS;  // global variables
int COLS;
int NUM;

void walkAndChop(Dwarf & dwarf, int r, int c, ostream &log){
  static bool chopWest = false;
  static bool chopEast = false;
  static bool chopSouth = false;
  static bool chopNorth = false;
  
  if (chopWest){
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    chopWest = false;
    return;
  }
  else if (chopEast){
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    chopEast = false;
    return;
  }
  else if (chopNorth){
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    chopNorth = false;
    return;
  }
  else if (chopSouth){
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    chopSouth = false;
    return;
  }
  
  if (dwarf.look(r, c+1) == EMPTY && dwarf.look(r, c+1) != DWARF){
    log << "Walk to " << r << " " << c+1 << endl;
    chopWest = true;
    dwarf.start_walk(r, c+1);
  }
  else if (dwarf.look(r, c-1) == EMPTY && dwarf.look(r, c-1) != DWARF){
    log << "Walk to " << r << " " << c-1 << endl;
    chopEast = true;
    dwarf.start_walk(r, c-1);
  }
  else if (dwarf.look(r+1, c) == EMPTY && dwarf.look(r+1, c) != DWARF){
    log << "Walk to " << r+1 << " " << c << endl;
    chopNorth = true;
    dwarf.start_walk(r+1, c);
  }
  else if (dwarf.look(r-1, c) == EMPTY && dwarf.look(r-1,c) != DWARF){
    log << "Walk to " << r-1 << " " << c << endl;
    chopSouth = true;
    dwarf.start_walk(r-1, c);
  }
}

void walkAndPick(Dwarf & dwarf, int r, int c, ostream &log){
  static bool pickWest = false;
  static bool pickEast = false;
  static bool pickSouth = false;
  static bool pickNorth = false;
  
  if (pickWest){
    log << "Found a tree -- chop" << endl;
    dwarf.start_pick(WEST);
    pickWest = false;
    return;
  }
  else if (pickEast){
    log << "Found a tree -- chop" << endl;
    dwarf.start_pick(EAST);
    pickEast = false;
    return;
  }
  else if (pickNorth){
    log << "Found a tree -- chop" << endl;
    dwarf.start_pick(NORTH);
    pickNorth = false;
    return;
  }
  else if (pickSouth){
    log << "Found a tree -- chop" << endl;
    dwarf.start_pick(SOUTH);
    pickSouth = false;
    return;
  }
  
  if (dwarf.look(r, c+1) == EMPTY && dwarf.look(r, c+1) != DWARF){
    log << "Walk to " << r << " " << c+1 << endl;
    pickWest = true;
    dwarf.start_walk(r, c+1);
  }
  else if (dwarf.look(r, c-1) == EMPTY && dwarf.look(r, c-1) != DWARF){
    log << "Walk to " << r << " " << c-1 << endl;
    pickEast = true;
    dwarf.start_walk(r, c-1);
  }
  else if (dwarf.look(r+1, c) == EMPTY && dwarf.look(r+1, c) != DWARF){
    log << "Walk to " << r+1 << " " << c << endl;
    pickNorth = true;
    dwarf.start_walk(r+1, c);
  }
  else if (dwarf.look(r-1, c) == EMPTY && dwarf.look(r-1,c) != DWARF){
    log << "Walk to " << r-1 << " " << c << endl;
    pickSouth = true;
    dwarf.start_walk(r-1, c);
  } 
}

void linearChop(Dwarf & dwarf, ostream &log){
  static bool chopW = false;
	static bool chopE = false;
	static bool chopN = false;
	static bool chopS = false;
    
   if (chopW){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      chopW = false;
      dwarf.start_chop(WEST);
      return;
    }
  }
  else if (chopE){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      chopE = false;
      dwarf.start_chop(EAST);
      return;
    }
  }
  else if (chopN){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
			chopN = false;
      dwarf.start_chop(NORTH);
      return;
    }
  }
  else if (chopS){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
			chopS = false;
      dwarf.start_chop(SOUTH);
      return;
    }
  }
  
  if (dwarf.name() == 0){
    for (int x = 0; x < ROWS; x++){
      for (int y = 0; y < COLS; y++){
        if (dwarf.look(x,y+1) == EMPTY && (dwarf.look(x,y) == PINE_TREE || dwarf.look(x,y) == APPLE_TREE)){
          chopW = true;
          dwarf.start_walk(x,y+1);
        }
        else if (dwarf.look(x,y-1) == EMPTY && (dwarf.look(x,y) == PINE_TREE || dwarf.look(x,y) == APPLE_TREE)){
          chopE = true;
          dwarf.start_walk(x,y-1);
        }
        else if (dwarf.look(x+1,y) == EMPTY && (dwarf.look(x,y) == PINE_TREE || dwarf.look(x,y) == APPLE_TREE)){
          chopN = true;
          dwarf.start_walk(x+1,y);
        }
        else if (dwarf.look(x-1,y) == EMPTY && (dwarf.look(x,y) == PINE_TREE || dwarf.look(x,y) == APPLE_TREE)){
          chopS = true;
          dwarf.start_walk(x-1,y);
        }
      }
    }
  } 
}

/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {

  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
  int closestrow = 0;
  int closestcol = 0;
  int closestrowApple = 0;  
  int closestcolApple = 0;
  double minDistance = INT_MAX;
  double minDistanceA = INT_MAX;
  double Distance = 0;
  double DistanceA = 0;
  
	for (int a = 0; a < ROWS; a++){   //Distance Formula for trees
	  for (int b = 0; b < COLS; b++){
      if (dwarf.look(a, b) == PINE_TREE){
    	  Distance = sqrt(pow(r - a, 2) + pow(c - b, 2));
    	  if (Distance < minDistance){
          closestrow = a;
         	closestcol = b;
         	minDistance = Distance;
        }
      }
   	}
  }
    
  for (int a = 0; a < ROWS; a++){   //Distance Formula for apples
    for (int b = 0; b < COLS; b++){
      if (dwarf.look(a, b) == APPLE_TREE){
        DistanceA = sqrt(pow(r - a, 2) + pow(c - b, 2));
        if (DistanceA < minDistanceA){
          closestrowApple = a;
          closestcolApple = b;
          minDistanceA = DistanceA;
        }
      }
    }
  }
    
  /*linearChop(dwarf, log);
    
  if (fenceW){
    if (dwarf.name() == 0){
      dwarf.start_build(WEST);
      fenceW = false;
      return;
    }
  }
    
	if (dwarf.name() == 0 && dwarf.lumber() > 10){
  	if (dwarf.look(5,0) == EMPTY){
      dwarf.start_walk(5,1);
      fenceW = true;
    }
  }*/
    
   if (dwarf.lumber() < 250){
     walkAndChop(dwarf, closestrow, closestcol, log);  
   }
   else {
     walkAndPick(dwarf, closestrowApple, closestcolApple, log);
   } 

  return;
}
