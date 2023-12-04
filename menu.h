#pragma once
#include "tvshow.h"
#include "unomap.h"
#include "tree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

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
long long int MeasureUnorderedMapTime(uno_map& showMap, const std::string& showName) {
    auto start = std::chrono::high_resolution_clock::now();

    TVshow picked = showMap.find(showName);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    //return duration.count();
}

long long MeasureTrieTime( Trie& trie, const std::string& showName) {
    auto start = std::chrono::high_resolution_clock::now();

    TVshow* foundShow = trie.find(showName);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return duration.count();
}


void ShowData(TVshow& show, uno_map& showmap, const std::string& showName) {
    cout << "Name : " << show.getName() << endl;
    cout << "Number of Seasons : " << show.getNumSeasons() << endl;
    cout << "Number of Episodes : " << show.getNumEpisodes() << endl;
    cout << "Number of Votes : " << show.getVoteCount() << endl;
    cout << "Vote Average : " << show.getVoteAverage() << endl;
    cout << '"' << show.getTagLine() << '"' << endl;
    cout << "Genres : " << show.getGenres() << endl;
    cout << "Languages : " << show.getLanguages() << endl;
    cout << "Networks : " << show.getNetworks() << endl;
    cout << "Episode Runtime : " << show.getEpRuntime() << endl;
    long long unoMapTime = MeasureUnorderedMapTime(showmap, showName);
    cout << "Time taken by uno_map to find a show: " << unoMapTime << " microseconds" << std::endl;
   
}


void ShowTree(TVshow* showPtr,Trie& trie, const std::string& showName) {
    if (showPtr) {
        cout << "Name From Tree : " << showPtr->getName() << endl;
        long long trieTime = MeasureTrieTime(trie,showName);
        cout << "Time taken by Trie to find a show: " << trieTime << " microseconds" << std::endl;
        cout << endl;

    } else {
        cout << "Show not found in the trie." << endl;
    }
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
