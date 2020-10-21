#include "Category.h"
#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

void Category::setCategory(string name) {
  reference = name;
}

void Category::addArtist(string artist) {
  artists.insert(artist);
}
void Category::deleteArtist(string artist) {
  artists.erase(artist);
}