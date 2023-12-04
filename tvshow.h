#pragma once
#include "tvshow.h"
#include <iomanip>
#include <iostream>
#include <string>

using std::string;

class TVshow {

private:
    // characteristics of the show.
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

public:
    /*============== CONSTRUCTOR =============== */
    // default constructor
    TVshow();

    TVshow(string name);
    TVshow(string name, int seasons, int episodes,
           int vote, float average, string tag,
           string genre, string language, string network,
           int runtime);

    string getName();
    int getNumSeasons();
    int getNumEpisodes();
    int getVoteCount();
    float getVoteAverage();
    string getTagLine();
    string getGenres();
    string getLanguages();
    string getNetworks();
    int getEpRuntime();
};

TVshow::TVshow() : numSeasons(0), numEpisodes(0), voteCount(0), voteAverage(0), epRuntime(0) {}

TVshow::TVshow(string name, int seasons, int episodes,
               int vote, float average, string tag,
               string genre, string language, string network,
               int runtime) {
    this->name = name;
    this->numSeasons = seasons;
    this->numEpisodes = episodes;
    this->voteCount = vote;
    this->voteAverage = average;
    this->tagline = tag;
    this->genres = genre;
    this->languages = language;
    this->networks = network;
    this->epRuntime = runtime;

}

TVshow::TVshow(string name) {
    this->name = name;
    this->numSeasons = 0;
    this->numEpisodes = 0;
    this->voteCount = 0;
    this->voteAverage = 0.0;
    this->tagline = "None";
    this->genres = "None";
    this->languages = "None";
    this->networks = "None";
    this->epRuntime = 0;
}

string TVshow::getName() {
    return name;
}

int TVshow::getNumSeasons() {
    return numSeasons;
}

int TVshow::getNumEpisodes() {
    return numEpisodes;
}
int TVshow::getVoteCount() {
    return voteCount;
}

float TVshow::getVoteAverage() {
    return voteAverage;
}

string TVshow::getTagLine() {
    return tagline;
}

string TVshow::getGenres() {
    return genres;
}

string TVshow::getLanguages() {
    return languages;
}

string TVshow::getNetworks() {
    return networks;
}

int TVshow::getEpRuntime() {
    return epRuntime;
}
