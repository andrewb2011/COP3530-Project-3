#pragma once
#include "./tvshow.h"
#include "unomap.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void MainMenu() {

    cout << "\n1. Search by TV show name." << endl;
    cout << "2. Get TV show recommendations." << endl;
    cout << "3. Return to Main Menu." << endl;
    cout << "4. Quit program." << endl;
}

void RetrievingData() {

    cout << "Retrieving Data" << endl;
}

void ShowData(TVshow& show) {

    cout << "Name : " << show.getName() << endl;
    cout << "Number of Seasons : " << show.getNumSeasons() << endl;
    cout << "Number of Episodes : " << show.getNumEpisodes() << endl;
    cout << "Number of Votes : " << show.getVoteCount() << endl;
    cout << "Vote Average : " << show.getVoteAverage() << endl;
    if (show.getTagLine() != "null") 
        cout << '"' << show.getTagLine() << '"' << endl;
    cout << "Genres : " << show.getGenres() << endl;
    cout << "Languages : " << show.getLanguages() << endl;
    cout << "Networks : " << show.getNetworks() << endl;
    cout << "Episode Runtime : " << show.getEpRuntime() << endl;
}

bool compareShows(TVshow& show1, TVshow& show2) {
    return show1.getVoteAverage() > show2.getVoteAverage();
}

vector<TVshow> getTopRatedShows(uno_map& showmap) {

    vector<TVshow> allShows;

    bool* arr = showmap.getArr();
    TVshow* shows = showmap.getShows();


    for (int i = 0; i < showmap.getSize(); i++) {
        if (arr[i] && shows[i].getVoteCount() >= 100)
            allShows.push_back(shows[i]);
        
    }

    sort(allShows.begin(), allShows.end(), compareShows);

    // This was orginally returning 10 shows, but changed to return all shows sorted for loop in main()
    //int numbertoshow = min(10, static_cast<int>(allShows.size()));
    //vector<TVshow> top10Shows(allShows.begin(), allShows.begin() + numbertoshow);

    //return top10Shows;
    return allShows;
}

vector<TVshow> getShowsNumSeasons(uno_map& showmap, int& numSeasons) {
    // This function is similiar to one above

    // this is new vector containing all shows with given number of seasons
    vector<TVshow> showsWithnumSeasons;

    bool* arr = showmap.getArr();
    TVshow* shows = showmap.getShows();

    for (int i = 0; i < showmap.getSize(); i++) {
        if (arr[i] && shows[i].getNumSeasons() == numSeasons && shows[i].getVoteCount() >= 100)
            showsWithnumSeasons.push_back(shows[i]);

    }

    sort(showsWithnumSeasons.begin(), showsWithnumSeasons.end(), compareShows);

    return showsWithnumSeasons;
}
