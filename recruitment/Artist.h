// Header file for Artist containing the artist class specification

#ifndef ARTIST_H
#define ARTIST_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<set>

using namespace std;

class Artist {
  public:
	  string name;
	  int age, jazzXP;
    // Keys: Instruments, values: years
    unordered_map<string, int> experience;
    // Subgenres
    unordered_set<string> styles;
    // Designated bands
    vector<string> roster;
    unordered_map<string, int> getExperience();
    unordered_set<string> getStyles();
    vector<string> getBands();

    void setName(string title);
    void setAge(int n);
    void setJazzXP(int n);
    void setExperience(string instrument, int years);
    void addStyle(string style);


  private:
  protected:
};


#endif // ARTIST_H