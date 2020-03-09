/*Deondre De Freitas
Course: CSCI 135
Assignment: Project 3A
Optimized program that will collect 100 lumber in less than 18 hours*/

#include <climits>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

bool chopW = false;
bool chopE = false;
bool chopN = false;
bool chopS = false;

bool fenceE = false;
bool fenceW = false;
bool fenceN = false;
bool fenceS = false;

bool Dwarf0 = true;
bool Dwarf1 = false;

int fences = 0;

int ROWS;  // global variables
int COLS;
int NUM;

void WalkAndChop(Dwarf & dwarf, int r, int c, ostream &log){
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
  double minDistance = INT_MAX;
  double Distance = 0;
  
  for (int a = 0; a < ROWS; a++){   //Distance Formula
    for (int b = 0; b < COLS; b++){
        if (dwarf.look(a, b) == PINE_TREE || dwarf.look(a, b) == APPLE_TREE){
          Distance = sqrt(pow(r - a, 2) + pow(c - b, 2));
          if (Distance < minDistance){
            closestrow = a;
            closestcol = b;
            minDistance = Distance;
          }
        }
      }
    }
  
  if (chopW){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(WEST);
      chopW = false;
      return;
    }
  }
  else if (chopE){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(EAST);
      chopE = false;
      return;
    }
  }
  else if (chopN){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(NORTH);
      chopN = false;
      return;
    }
  }
  else if (chopS){
    if (dwarf.name() == 0){
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(SOUTH);
      chopS = false;
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
  
  if (fenceW){
    if (dwarf.name() == 1){
      log << "Fence Built" << endl;
      dwarf.start_build(WEST);
      fenceW = false;
      fences++;
      return;
    }
  }
  else if (fenceN){
    if (dwarf.name() == 2){
      log << "Fence Built" << endl;
      dwarf.start_build(NORTH);
      return;
    }
  }
  
  if (dwarf.lumber() > 130-(fences*10)){  //If dwarves have enough lumber, then begin building
    if (dwarf.name() == 1){
      if (dwarf.look(0,0) == EMPTY){
       dwarf.start_walk(0,1);
       fenceW = true;
       return;
     }
      for (int i = 0; i < ROWS; i++){
       for (int j = 0; j < COLS; j++){
          if (dwarf.look(i,j) == FENCE){
            dwarf.start_walk(i,j+fences);
            fenceW = true;
            return;
         }
         else if (dwarf.look(i,j+fences) == FENCE){
           dwarf.start_walk(i,fences+2);
           fenceW = true;
           return;
         }
        }
      }
    }
  }
  
  if (dwarf.name() == 2){
    if (dwarf.lumber() >= 10 && dwarf.lumber() <= 300){
      for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
          if (dwarf.look(x,y) == FENCE && dwarf.look(x+1,y) == EMPTY){
            dwarf.start_walk(x+2,y);
            fenceN = true;
            return;
          }
        }
      }
    }
  }
  
  WalkAndChop(dwarf, closestrow, closestcol, log);

  return;
}
