#include "Artist.h"
#include "Band.h"
#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

void Band::changeGenre(unordered_set<string> newGenre) {
  genre = newGenre;
}

void Band::changeName(string newName) {
  name = newName;
}

void Band::addMember(string artist) {
  members.insert(artist);
}

void Band::deleteMember(string artist) {
  members.erase(artist);
}