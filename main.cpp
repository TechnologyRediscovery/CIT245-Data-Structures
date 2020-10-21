/*
Purpose: Jazz artist recruitment program
NOTES/ISSUES:
  15-Sept-2020
  - Still deciding on whether it makes sense to create a menu structure or not. It doesn't seem entirely necessary to make each submenu objects, but it could clean up the code nicely.
TO-DO:
  - Create band
  - Delete band
  - Modify band
  - Extra: Scoring
*/

#include<iostream>
#include<string>
#include<map>
#include<unordered_map> 
#include<unordered_set>
#include<vector>
#include<algorithm>
#include<stdexcept>
#include<set>
#include "recruitment/Artist.h"

using namespace std;

/*
GLOBALS
*/

unordered_set<string> instruments = { "Bass", "Clarinet", "Flute", "Guitar", "Harp", "Percussion", "Piano", "Saxophone", "Trumpet", "Trombone" };

unordered_set<string> styles = { "Swing", "Free", "Bebop", "Spiritual", "Cool", "Latin", "Fusion", "Traditional" };

vector<Artist> artists;
vector<string> menu_options = { "0. Exit\n", "1. Review artist roster\n", "2. Enter a new artist\n", "3. Delete an artist.\n", "4. Create new band.\n", "5. Delete band.\n" };

// key: style; value: set of relevant artists 
map<string, unordered_set<string>> artistsByStyle;

// key: instrument; value: set of relevant artists
map<string, unordered_set<string>> artistsByInstrument;

// Creates map keys that will later categorize artists
void createRosterMaps() {
  for (string style: styles) {
    artistsByStyle[style];
  }
  for (string instrument: instruments) {
    artistsByInstrument[instrument];
  }
}

// Handles improper user input
void error(string x) {
	if (x == "invalid arg") {
		throw invalid_argument(x);
		cout << endl;
	}
	else if (x == "out of range") {
		throw out_of_range(x);
		cout << endl;
	}
	else {
		cerr << x;
		cout << endl;
	}
	// reference for clear function: "Principles and Practies Using C++" (Stroustrup; pg 355)
	cin.clear(); // clears input stream
}

// // Adds artist to unordered maps 
void categorizeArtist(Artist artist) {
  // for (auto it = artist.experience.begin(); it != artist.experience.end(); ++it) {
  //   string instrument = it->first;
  //   artistsByInstrument.make_pair(instrument, artist);
  //   cout << endl << artistsByInstrument[instrument].size() << " artists play " << instrument << endl;
  // }
  // for (string style: artist.styles) {
  //   artistsByStyle[style].insert(artist);
  //   cout << endl << artistsByStyle[style].size() << " artists play " << style << endl;
  // }
}


/**
OUTPUT 
**/

// Shows user the current roster lineup
void outputAllArtists() {
  cout << endl << "CURRENT ARTISTS" << endl;
    for (Artist artist : artists) {
      cout << artist.name << endl;
    }
  cout << endl << endl;
}

// Shows user information about existent artist on roster
void outputArtistInfo(Artist artist) {
  cout << "Age: " << artist.age << endl;
  cout << "Years playing jazz: " << artist.jazzXP << endl;
  // Resource: https://www.geeksforgeeks.org/traverse-values-given-key-multimap/
  // Iterates over artist's instrument listing
  for (auto it = artist.experience.begin(); it!=artist.experience.end(); ++it) {
    // first is the key; second is the value
    cout << "Years playing " << it->first << ": " << it->second << endl;
  }
  cout << "Jazz styles: ";
  // Iterates over artist's styles
  for (string style: artist.styles) {
    cout << style << "\t";
  }
  cout << endl;
}


// Shows user the available styles to select from
void outputStyles() {
	cout << endl << "Choose from the following listed: " << endl;
	for (string x : styles) {
		cout << x << endl;
	}
	cout << endl;
}

// Shows user the available instruments to select from
void outputInstruments() {
	cout << endl << "Choose from the following listed: " << endl;
	for (string x : instruments) {
		cout << x << endl;
	}
	cout << endl;
}

// Shows user the available menu options to select from
void outputMainMenu() {
	cout << endl << "Please select one of the following options:" << endl << endl;
  // presents menu options
	for (int i = 0; i < menu_options.size(); ++i) {
		cout << menu_options[i];
	}
  cout << endl;
}

/**
VALIDATION CHECKS
**/

// Prohibits user from responding other than yes or no
string validConfirmation(string response) {
    cin >> response;
    // Infinite loop until user enters yes or no
    while (response != "yes" && response != "no") {
      cout << endl << "Please type \"yes\" or \"no\"" << endl;
      cin >> response;
    }
    if (response == "yes") { return "yes"; }
    else { return "no"; }
}

bool validNewName(string name) {
  if (!isalnum(name[0])) {
    error("Please enter a name without a whitespace as the first character.");
  }
  for (Artist artist : artists) {
    if (artist.name == name) {
      cout << endl << "The name " << name << "is already taken." << endl;
      error("Please submit a different name.\n");
      return false;
    }
  } return true;
}

// Checks for valid name. Returns Artist struct
Artist validName(Artist newArtist, string name) {
  // Any name that doesn't start with whitespace is valid.
	while (!validNewName(name)) {
    // Resource for getline: https://www.cplusplus.com/reference/string/string/getline/
		getline(cin, name);
	}
	newArtist.setName(name); // Sets newArtist's name
	return newArtist;
}

// Checks for valid age. Returns Artist struct
Artist validAge(Artist newArtist, int age) {
  // An artist cannot be 0 or of negative age
	while (age <= 0) {
		error("invalid arg");
		cin >> age;
	}
	newArtist.setAge(age);  // Sets newArtist's name
	return newArtist;
}

// Checks for valid years of experience. Returns Artist struct
Artist validXP(Artist newArtist, int xp) {
  // An artist cannot have negative or 0 years of experience and 
  // their experience can't be greater than their age
	while (xp <= 0 || newArtist.age < xp) {
		error("invalid arg");
		cin >> xp;
	}
	newArtist.setJazzXP(xp);  // Sets newArtist's experience
	return newArtist;
}



// Checks user's response for valid instrument. Returns Artist struct
Artist validInstruments(Artist newArtist, string instrument) {
	string response = "";
	while (true) {
    // Resource for searching in a set for an element: 
    // https://www.geeksforgeeks.org/set-find-function-in-c-stl/
    // Checks for response in instrument's set
		if (instruments.find(instrument) != instruments.end()) {
			string years;
			cout << endl << "How many years have you played " + instrument + " ?" << endl;
			cin >> years;
      // The artist cannot have experience with an instrument for less than 0 years 
      // or experience greater than their age 
			while (stoi(years) <= 0 || newArtist.age < stoi(years)) {
				cout << endl << "Enter a valid integer for years you have played " + instrument + " :" << endl;
				cin >> years;
			}
      // Sets artist's experience with an instrument for specified years
			newArtist.setExperience(instrument, stoi(years));
			cout << endl << "Is there another instrument that you can play? Enter \"yes\" or \"no\"." << endl;
      response = validConfirmation(response);
      // Artist does not have anymore instruments to add
			if (response == "no") {
				cin.clear();
				return newArtist;
			}
      // Continue adding instruments to artist's resume
			else if (response == "yes") {
				instrument = "";
				cin.clear();
        /* RESOURCE: 
        https://www.tutorialspoint.com/what-is-the-use-of-cin-ignore-in-cplusplus 
				*/
        cin.ignore();
			}
		}
    // Prohibits responses that are not found in the instrument's set
		else {
			error("\nPlease select from the instruments listed below.");
			outputInstruments();
			cin >> instrument;
		}
	}
}

// Checks user's response for valid input. Returns Artist struct
Artist validStyle(Artist newArtist, string style) {
	string response = "";
	while (true) {
    // Checks for response in style's set
		if (styles.find(style) != styles.end()) {
      newArtist.styles.insert(style);
			cout << endl << "Is there another style that you can play? Enter \"yes\" or \"no\"." << endl;
			response = validConfirmation(response);
      // Artist does not have anymore styles to add
			if (response == "no") {
				cin.clear();
				return newArtist;
			}
      // Continue adding styles to artist's resume
			else if (response == "yes") {
				style = "";
				cin.clear();
				cin.ignore();
			}
		}
    // Prohibits responses that are not found in the style's set
		else {
			error("\nPlease select from the styles listed below.");
			outputStyles();
			getline(cin, style);
		}
	}
}

// Shows user information about an artist if existent and returns their index 
// within the artists vector
int validArtist() {
  string artist = "";
  while (true) {
    getline(cin, artist);
    for (int i = 0; i < artists.size(); ++i) {
      if (artists.at(i).name == artist) {
        return i;
      }
    }
    // Artist was not found in the roster
    error("\nPlease select from the artists listed below.");
    cin.clear();
    outputAllArtists();
  }
}



/**
SUBMENU  
**/

// Creates new artist struct
void submenuCreateArtist() {
	cin.ignore();
	Artist newArtist;
	string input = "";
	int progress = 0;
	vector<string> questions = { "\nEnter your artist name: ", "\nHow old are you?", "\nHow long have you played jazz? ", "\nWhich instrument(s) can you play?", "\nWhat styles of jazz can you play?" };
	cout << endl << "Type \"reset\" if you would like to restart the process.";
  cout << endl << "Type \"quit\" if you would like to quit the process." << endl;
	// Infinite loop until an artist is finally created
  while (true) {
		cout << questions.at(progress) << endl;
    // output for available instruments
		if (progress == 3) {
			outputInstruments();
		} // output for available styles
		else if (progress == 4) {
			outputStyles();
		}
		getline(cin, input);
		try {
      // Start from the top
			if (input == "reset") {
				progress = 0;
			}
      else if (input == "quit") {
        return;
      }
			else {
        switch (progress) {
          case 0: 
            newArtist = validName(newArtist, input);
            break;
          case 1:
            newArtist = validAge(newArtist, stoi(input));
            break;
          case 2: 
            newArtist = validXP(newArtist, stoi(input));
            break;
          case 3:
            newArtist = validInstruments(newArtist, input);
            break;
          case 4:
            newArtist = validStyle(newArtist, input);
            artists.push_back(newArtist); // Adds artist to roster
            categorizeArtist(newArtist);
            return;
            break; // for good practice, but definitely not necessary
        }
				cin.clear();
				progress++; // Continues the artist creation questionnaire until we return
      }
		}
    // Alerts user of incorrect input
	  catch (invalid_argument) {
		  cerr << "Invalid submission. Try again. " << endl;
	  }	
  }
}

// Roster interface
void submenuRoster(string option) {
  string response = "";
  // No artists on roster
  if (artists.size() == 0) {
    cout << "There are currently no artists on the roster." << endl;
  }
  // Lists artists on roster
  else {
    while (true) {
      outputAllArtists();
      cout << endl << "Select the artist of interest." << endl;
      int index = validArtist();
      if (option == "view") {
        outputArtistInfo(artists[index]);
      }
      else if (option == "delete") {
        // Resource for begin method: https://www.cplusplus.com/reference/vector/vector/erase/
        artists.erase(artists.begin() + index);
      }
      cin.clear();
      if (artists.size() == 0) {
        cout << "There are currently no more artists on the roster." << endl;
        return;
      }
      cout << endl << "Would you like to select another artist? Enter \"yes\" or \"no\"." << endl;
      response = validConfirmation(response);
      // Artist does not have anymore instruments to add
			if (response == "no") {
				cin.clear();
				return;
			}
      if (response == "yes") {
				response = "";
				cin.clear();
				cin.ignore();
			}
    }
  }
}

void submenuBand(string option) {
  if (option == "create") {
    // band specs
      // by instruments
      // by style
      // by experience
  }
  if (option == "delete") {
    // validBand call similar to validArtist
  }

  if (option == "view") {
    // outputBand call similar to outArtistInfo
  }
}

// Roster deletion interface
void submenuRemoveArtist(int size) {
  // No artists on roster
  if (size == 0) {
    cout << "There are currently no artists on the roster to remove." << endl;
  }
  // Lists artists on roster
  else {
    outputAllArtists();
    cout << endl << "Which artist would you like to remove from the agency?";
  }
}

// Band  creation interface
void submenuCreateBand() { 
  // do something
}

// Band removal interface
void submenuRemoveBand() {
  // do something
}

// Interface for submenu
void goToSubmenu(int n) {
	cin.clear();
	switch (n) {
    // Views artist roster
	  case 1:
      submenuRoster("view");
		  outputMainMenu();
		  return;

    // Creates new artist
    case 2:
      submenuCreateArtist();
      outputMainMenu();
      return;

    // Removes artist from roster
    case 3:
      submenuRoster("delete");
      outputMainMenu();
      return;

    // Create a new band
    case 4:
      submenuBand("create");
      outputMainMenu();
      return;

    // Remove band from roster
    case 5:
      submenuBand("delete");
      outputMainMenu();
      return;

    // This shouldn't actually happen  
	  default:
	  	return;
	}
}

// Interface for the main menu
void menu() {
	bool active = true;
	string choice;
	cout << "Welcome to the main menu. Please select one of the following options:" << endl << endl;
	outputMainMenu();
	// infinite loop until user quits menu
	do {
		try {
			cin >> choice;
			// reference for stoi function: https://www.geeksforgeeks.org/converting-strings-numbers-cc/
			// valid input can only be the integer values provided in the menu dialogue.
			menu_options.at(stoi(choice));
			if (stoi(choice) != 0) {
				goToSubmenu(stoi(choice));
				choice = "";
			}
			else {
				cout << endl << "Ending the future jazz agency program." << endl;
				active = false;
			} 
		}  // Alerts user of incorrect input
		catch (out_of_range) {
			cerr << "Integer out of range. " << endl;
			outputMainMenu();
		} // Alerts user of incorrect input
		catch (invalid_argument) {
			cerr << "Please use an appropriate integer value. " << endl;
			outputMainMenu();
		}
	} while (active);
}


int main() {
  // createRosterMaps();
	// menu();
  
}