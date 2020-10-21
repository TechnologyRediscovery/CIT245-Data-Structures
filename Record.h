#ifndef RECORD_H
#define RECORD_H

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>

using namespace std;

class Record {
  public:
    Record (string title, string artist, int length, int year);


    // Modifiers
    void setTitle(string name);
    void setArtist(string name);
    void setTrack(string trackNum, string trackName);
    void setLength(int time);
    void setYear(int date);

    // Accessors
    string getTitle();
    string getArtist();
    map<string, string> getTracks();
    int getLength();

  private:
    // Class attributes
    string title, artist;
    map<string, string> tracks; // Side and track number, track name
    int length, year;
};

#endif // RECORD_H