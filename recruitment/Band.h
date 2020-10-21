#ifndef BAND_H
#define BAND_H

#include "Artist.h"
#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

// Creates a band struct
struct Band {
  string name;
  unordered_set<string> genre;
  unordered_set<string> members;

  void changeGenre(unordered_set<string> newGenre);
  void changeName(string newName);
  void addMember(string artist);
  void deleteMember(string artist);
};

#endif // BAND_H