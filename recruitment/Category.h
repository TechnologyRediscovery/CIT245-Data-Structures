#ifndef CATEGORY_H
#define CATEGORY_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

struct Category {
  string reference;
  unordered_set<string> artists;

  void setCategory(string name);
  void addArtist(string artist);
  void deleteArtist(string artist);
};

#endif // CATEGORY_H