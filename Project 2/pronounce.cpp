/*Author: Deondre De Freitas
Course: CSCI 136
Assignment Project 2 Phase 3
Prints the pronunciation of a word and any words that are similar and words that can be made by replacing one phoneme*/

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;

bool ignoreSymbols(string str){//Boolean function to check for parentheses and avoid in the file
  for (int j = 0; j < str.length(); j++){
    if (str[j] == '('){
      return true;
    }
  }
  return false;
}

void splitOnSpace(string s, string &before, string &after){//Function used in splitting strings
  before = "";
  after = "";

  int i = 0;

  while (i < s.size() && not isspace(s[i])) {
    before += s[i]; i++;
    }
  i++;

  while (i < s.size()) {
    after += s[i]; i++;
  }
}

int CountSpace(string pronun){
  int count = 0;
  for (int i = 0; i < pronun.length(); i++){
    if (pronun[i] == ' '){
      count++;
    }
  }
  return count;
}

string identical(string pronun, string word){//Reopens file to look for identical words
  string line, before, pronunciation, junk, iden;

  ifstream fin ("cmudict.0.7a");
  if (fin.fail()) {
    cerr << "File cannot be read." << endl;
    exit(1);
  }
  for (int i = 0; i < 54; i++){
    getline(fin, junk);//Gets rid of first few lines of file
  }

  while (getline(fin, line)) {
    splitOnSpace(line, before, pronunciation);
    if (pronun == pronunciation && before != word) {//If the pronunciation is equal to the given parameter and not equal to the inputted word
      iden += (before + ' ');
    }
  }
  return iden;
}

string replace(string toReplace){//Function to replace phonemes
  string junk, new_before, new_after, before, after, dictword, dictphoneme, line;
  int spaces;
  int difference = 0;
  string str = "";

   spaces = CountSpace(toReplace);

   ifstream fin("cmudict.0.7a");
  if (fin.fail()) {
    cerr << "File cannot be read." << endl;
    exit(1);
  }

  for (int i = 0; i < 54; i++){
    getline(fin, junk);
  }
  while (getline(fin, line)){
    new_after = toReplace;//Save the value of the origninal input
    difference = 0;
    splitOnSpace(line, dictword, dictphoneme);
    if (CountSpace(dictphoneme) == spaces){
      for (int i = 0; i < spaces + 1; i++){//Split the pronunciation and check each phoneme
        splitOnSpace(dictphoneme, before, dictphoneme);
        splitOnSpace(new_after, new_before, new_after);
        if (before != new_before){
          difference++;
        }
      }
        if (difference == 1 && ignoreSymbols(dictword) == false){//If only one difference is found then add a space for multiple outputs and return
          str += (' ' + dictword);
        }
    }
  }
  return str;
}

string add(string toAdd){//"Add" function similar to replace function
  string junk, line, original, dictword, dictphoneme, before, new_before, x, y;
  int spaces, difference;
  string str = "";
  int counted;

  spaces = CountSpace(toAdd);

  ifstream fin("cmudict.0.7a");
  if (fin.fail()) {
    cerr << "File cannot be read." << endl;
    exit(1);
  }

  for (int i = 0; i < 54; i++){
    getline(fin, junk);
  }

  while (getline(fin, line)){
    original = toAdd;
    difference = 0;
    splitOnSpace(line, dictword, dictphoneme);
    counted = CountSpace(dictphoneme);
    if (counted == spaces + 1){
      for (int i = 0; i < spaces + 2; i++){// "spaces + 1" is now "spaces + 2" to account for the last letter in the phonemes
        splitOnSpace(dictphoneme, before, dictphoneme);
        splitOnSpace(original, new_before, original);
        if (before != new_before){
          difference++;
          splitOnSpace(dictphoneme, before, dictphoneme);//Split on space again to compare when phonemes don't match
          if (new_before != before){
            difference++;//Increment again to avoid if more than one difference is found
          }
        }
      }
    }
      if (difference == 1 && ignoreSymbols(dictword) == false){
        str += dictword + ' ';
      }
   }
  return str;
}

string remove(string removed){//Removes one phoneme
  string junk, line, original, dictword, dictphoneme, before, new_before;
  int spaces, difference;
  string str = "";
  int counted;
  spaces = CountSpace(removed);

  ifstream fin("cmudict.0.7a");
  if (fin.fail()) {
    cerr << "File cannot be read." << endl;
    exit(1);
  }

  for (int i = 0; i < 54; i++){
    getline(fin, junk);
  }

  while (getline(fin, line)){
    original = removed;
    difference = 0;
    splitOnSpace(line, dictword, dictphoneme);
    counted = CountSpace(dictphoneme);
    if (counted == spaces - 1){//All words will have one less phoneme
      for (int i = 0; i <= spaces; i++){
        splitOnSpace(dictphoneme, before, dictphoneme);
        splitOnSpace(original, new_before, original);
        if (before != new_before){
          difference++;
          splitOnSpace(original, new_before, original);//Split on space again to compare when phonemes don't match
          if (new_before != before){
            difference++;
          }
        }
      }
      if (difference == 1 && ignoreSymbols(dictword) == false){//Ignore symbols and numbers
        str += dictword + ' ';
      }
    }

  }
  return str;
}

int main(int argc, char* argv[]){
  ifstream fin(argv[1]);//Keyword for file
  if (fin.fail()) {
    cerr << "File cannot be read or found. Please try again." << endl;//If file cannot be read
    exit(1);
  }

  string line, input, phoneme, junk, before, pronun;
  bool found = false;
  string new_str;
  string new_iden;
  string new_add;
  string new_remove;

  for (int i = 0; i < 54; i++){
    getline(fin, junk);//Gets rid of first 54 lines of file
  }

  cin >> input;

  for (int i = 0; i < input.length(); i++) {
    input[i] = toupper(input[i]);//Converts input to upper case regardless of case
  }

  while (getline(fin, line)) {
    splitOnSpace(line, before, pronun);
    if (input == before) {
      found = true;
      new_iden = identical(pronun, input);
      new_str = replace(pronun);
      new_add = add(pronun);
      new_remove = remove(pronun);

      cout << "Pronunciation    :" << pronun << endl << endl;
      cout << "Identical        : " << new_iden << " " << endl;
      cout << "Add phoneme      : " << new_add << endl;
      cout << "Remove phoneme   : " << new_remove << endl;
      cout << "Replace phoneme  :" << new_str << endl;
      break;
    }
  }
   if (!found) {//Boolean value created for easier use of the cout function if the word isn't found
     cout << "Not Found" << endl;
   }
  return 0;
}
