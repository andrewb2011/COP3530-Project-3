#include "unomap.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;


int main() {
  
    string name;
    int numSeasons;
    int numEpisodes;
    int voteCount;
    float voteAverage;
    string tagline;
    string genres;
    string languages;
    string networks;
    int epRuntime;

    uno_map showMap;

    ifstream inFS("UpdatedDatawithoutDQ.csv");
    

    if (!inFS.is_open()) {
        cout << "File could not be open" << endl;
        return 0;
    }
    else {
        string line;
        string token;

        //int counter = 0;
        while (getline(inFS, line)) {
            // std::cout << counter << std::endl;
            // counter++;
            istringstream inSS(line);

            // takes each column and puts it into correct variable
            try {
                getline(inSS, name, ',');       // variable for Movie/Show name
                // Check if the name is enclosed in double quotes
                if (!name.empty() && name.front() == '"') {
                    // If the name starts with a double quote, continue reading until the closing quote
                    string nextPart;
                    do {
                        getline(inSS, nextPart, ',');
                        name += ',' + nextPart;
                    } while (!nextPart.empty() && nextPart.back() != '"');
                }

                // Remove double quotes from the beginning and end of the name
                //name.erase(remove(name.begin(), name.end(), '"'), name.end());

                getline(inSS, token, ',');
                numSeasons = stoi(token);

                getline(inSS, token, ',');
                numEpisodes= stoi(token);

                getline(inSS, token, ',');
                voteCount = stoi(token);

                getline(inSS, token, ',');
                voteAverage = stof(token);

                getline(inSS, tagline, ',');

                getline(inSS, genres, ',');
                    while (getline(inSS, token, ',')) {
                        // Append each additional genre to the existing string
                        genres += ", " + token;
                }

                /*if (inSS.peek() == '"') {
                    //inSS.get();
                    getline(inSS, genres, '\"');
                }*/

                /*getline(inSS, genres, '\"');
                getline(inSS, genres, '\"');
                genres = genres.substr(1);*/

                /*getline(inSS, genres, ',');
                while (getline(inSS, token, ',')) {

                    if (token == "languages") 
                        break;  
                
                    // Append each additional genre to the existing string
                    genres += ", " + token;
                }*/

                getline(inSS, languages, ',');

                getline(inSS, networks, ',');

                getline(inSS, token, ',');
                epRuntime = stoi(token);

                // make instance of each show to add to map and tree
                TVshow show(name, numSeasons, numEpisodes, voteCount, voteAverage, tagline, genres, languages, networks, epRuntime);

                // add each TV show to map and tree.
                showMap.insert(show);

            }
            // This is used for debugging and tells my what line is affected
            catch (const std::exception& e) {
                cerr << "Error processing line: " << line << "\n" << e.what() << endl;      
            }

        }

    }
    inFS.close();

    
    cout << "Items in map: " << showMap.getSize() << endl;
    cout << "Collisions: " << showMap.collisions() << endl;
    
    TVshow picked = showMap.find("Game of Thrones");
    //ShowData(picked);

    /* ========== START OF PROGRAM ========== */

    cout << "Would you like to search for a TV show or get recommendations?" << endl;
    cout << "Enter a valid choice." << endl;

    bool RunProgram = true;
    int input;
    int choice;

    while (RunProgram) {

        MainMenu(); // this prints the prompt for user input.

        cin >> input;

        if (input == 1) {
            cout << "Enter name of TV show." << endl;
            cin.ignore();
            string showName;
            getline(cin, showName);

            cout << "Excellent choice!" << endl;

            picked = showMap.find(showName);
            ShowData(picked);


        }
        else if (input == 2) {
            cout << "AHH. I see you need a recommendation for a new show." << endl;

            // add second buffer here

            cout << "Would you like to search our database by rating or number of seasons?" << endl;

            cout << "1. Search by Rating." << endl;
            cout << "2. Search by Number of Seasons" << endl;

            int choice;

            cin >> choice;

             // maybe do a while loop just incase use inputs wrong number, it can go back to this point

            if (choice == 1) {
                // this searches shows by rating

                cout << endl;
                cout << "Here are the top 10 highest rated shows with atleast 100 ratings." << endl;

                // This function get the Top 10 highest rated shows w/ atleast 100 ratings and put them into this vector
                vector<TVshow> top10RatedShows = getTopRatedShows(showMap);
                
                int startingPoint = 0;
                int endingPoint = min(10, static_cast<int>(top10RatedShows.size()));

                for (int i = startingPoint; i < endingPoint; i++) {
                    cout << top10RatedShows[i].getName() << " - Rating: " << top10RatedShows[i].getVoteAverage() << endl;
                }
                
                // this ask for the next 10 numbers
                bool keepGoing = true;
                string YesorNo;

            
                while (keepGoing) {
                    cout << endl;
                    cout << "Would you like to get the next 10 shows? Yes or No" << endl;
                    
                    cin >> YesorNo;

                    if (YesorNo == "Yes" || YesorNo == "yes") {
                        // get next 10 shows from sorted list
                        startingPoint = endingPoint;
                        endingPoint = min(endingPoint + 10, static_cast<int>(top10RatedShows.size()));

                        for (int i = startingPoint; i < endingPoint; i++) {
                            cout << top10RatedShows[i].getName() << " - Rating: " << top10RatedShows[i].getVoteAverage() << endl; 
                        } 

                    }
                    else if (YesorNo == "No" || YesorNo == "no") {
                        keepGoing = false;
                    }
                    else {
                        cout << "Please enter yes or no." << endl;
                    }

                }


            }
            else if (choice == 2) {

                cout << "Enter a number from 0 to 240 representing the number of seasons the show has." << endl;
                cout << "Then the top rated shows with that many season will be displayed." << endl;
                
                int num;

                cin >> num;

                if (num < 0 || num > 240) {
                    cout << "There are no shows with that number of seasons. Try again." << endl;
                    continue;
                }
                else if (num >= 0 && num <= 240) {
                    // Here, make a vector will all shows with given number of season sorted by rating with atleast 100 ratings.
                    vector<TVshow> ShowsWithNumSeasons = getShowsNumSeasons(showMap, num);

                    if (ShowsWithNumSeasons.size() == 0){
                        cout << "There are no shows that have to number of seasons you requested." << endl;
                        continue;
                    }

                    int startingPoint = 0;
                    int endingPoint = min(10, static_cast<int>(ShowsWithNumSeasons.size()));

                    for (int i = startingPoint; i < endingPoint; i++) {
                        cout << ShowsWithNumSeasons[i].getName() << " - Rating: " << ShowsWithNumSeasons[i].getVoteAverage() << endl;
                    }
                    
                    // this ask for the next 10 numbers
                    bool keepGoing = true;
                    string YesorNo;

                
                    while (keepGoing) {
                        cout << endl;
                        cout << "Would you like to get the next 10 shows? Yes or No" << endl;
                        
                        cin >> YesorNo;

                        if (YesorNo == "Yes" || YesorNo == "yes") {
                            // get next 10 shows from sorted list
                            startingPoint = endingPoint;
                            endingPoint = min(endingPoint + 10, static_cast<int>(ShowsWithNumSeasons.size()));

                            for (int i = startingPoint; i < endingPoint; i++) {
                                cout << ShowsWithNumSeasons[i].getName() << " - Rating: " << ShowsWithNumSeasons[i].getVoteAverage() << endl; 
                            } 

                        }
                        else if (YesorNo == "No" || YesorNo == "no") {
                            keepGoing = false;
                        }
                        else {
                            cout << "Please enter yes or no." << endl;
                        }

                    }


                }
                else {
                    cout << "Please a correct number." << endl;
                    continue;
                }

            }
            else {
                cout << "Incorrect input. Please choose correct input" << endl;
                continue;
            }


        }
        else if (input == 3) {
            // This returns the user to the main menu
            // maybe dont need this

            // Maybe put a random show generator here.

            continue;
        }
        else if (input == 4) {
            // This exits the program. User is finished
            cout << "Thank you for using our Show Picker. GoodBye!" << endl;
            RunProgram = false;
            break;
        }
    }
    return 0;
}
