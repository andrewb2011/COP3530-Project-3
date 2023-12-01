#pragma once
#include "./tvshow.h"
#include <iostream>

#define MAX_SIZE 150000

class uno_map {
private:
    bool arr[MAX_SIZE];
    TVshow* shows = new TVshow[MAX_SIZE];
    int size;
    int num_collisions;

public:
    uno_map();
    int hash(std::string s);
    void insert(TVshow show);
    TVshow find(std::string name);
    int getSize();
    //debugging
    int collisions();

    // Added by Andrew to get top 10 Rated shows
    bool* getArr();
    TVshow* getShows();
};

uno_map::uno_map() {
    num_collisions = 0;
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = false;
    }
}

int uno_map::hash(std::string s) {
    return std::hash<std::string>{}(s) % MAX_SIZE;
}

void uno_map::insert(TVshow show) {
    int index = hash(show.getName());
    if (arr[index] == false) {
        arr[index] = true;
        shows[index] = show;
        size++;
    }
    // if there was a collision, use linear probing the go to the next free index. 
    else {
        while (arr[index]) {
            index = (index + 1) % MAX_SIZE;
        }
        arr[index] = true;
        shows[index] = show;
        size++;
    }
}

TVshow uno_map::find(std::string name) {
    int index = hash(name);
    if (shows[index].getName() == name)
        return shows[index];
    else {
        while (shows[index].getName() != name) {
            index = (index + 1) % MAX_SIZE;
        }
        return shows[index];
    }
}

int uno_map::getSize(){
    return size;
}

//debugging
int uno_map::collisions() {
    return num_collisions;
}

bool* uno_map::getArr() {
    return arr;
}
TVshow* uno_map::getShows() {
    return shows;
}
