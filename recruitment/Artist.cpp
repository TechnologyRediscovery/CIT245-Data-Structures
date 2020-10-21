// Implementation file for Artist
// Method definitions for Artist class
#include "Artist.h"
#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

unordered_map<string, int> Artist::getExperience() {
  return experience;
}
unordered_set<string> Artist::getStyles() {
  return styles; 
}
vector<string> Artist::getBands() {
  return roster;
}


void Artist::setName(string title) {
  name = title;
}

void Artist::setAge(int n) {
  age = n;
}

void Artist::setJazzXP(int n) {
  jazzXP = n;
}
void Artist::setExperience(string instrument, int years) {
  experience[instrument] = years;
}
void Artist::addStyle(string style) {
  styles.insert(style);
}




