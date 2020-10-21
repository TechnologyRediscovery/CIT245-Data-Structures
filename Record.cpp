#include "Record.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>

using namespace std;

Record::Record(string title, string artist, int length, int year) {
  setTitle(title);
  setArtist(artist);
  setLength(length);
  setYear(year);
}

void Record::setTitle(string name) {
  title = name;
}

void Record::setArtist(string name) {
  artist = name;
}

void Record::setTrack(string trackNum, string trackName) {
  tracks[trackNum] = trackName;
}

void Record::setLength(int time) {
  length = time; 
}

void Record::setYear(int date) {
  year = date;
}

string Record::getTitle() {
  return title;
}

string Record::getArtist() {
  return artist;
}

map<string, string> Record::getTracks() {
  return tracks; 
}

int Record::getLength() {
  return length; 
}

