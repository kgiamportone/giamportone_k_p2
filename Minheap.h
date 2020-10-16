#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <chrono>
#include <cstdlib>

class Contestant{
public:
    int id;// unique ID for each Contestant
    int points; // current number of points for Contestant

    Contestant(){}
    // ~Contestant(){}
    Contestant(int iD, int pointS) {
        this->id = iD;
        this->points = pointS;
    }
    int getID();
    int getPoints();
};

class Minheap {
public:
    Contestant * contestants; // min priority queue
    int * handle; // tracks location of contestants in heap
    int max_size; // size of array
    int latest_pos; // keeps track of most recent position inserted in heap

    Minheap(int n) : contestants(new Contestant[n+1]), handle(new int[n+1]) {
        this->max_size = n+1;
        latest_pos = 0; // keeps track of most recent position inserted in heap
        //contestants = NULL; // 'new' yes or no???
        //handle = NULL;
        // initialize handle
        for (int i = 0; i < n+1; i++) {
            handle[i] = -1;
        }

        // initialize heap?
        for (int i = 0; i < n+1; i++) {
            contestants[i] = Contestant(-1, -123); // default values
        }
    };
    // ~Minheap();
    int getMaxSize();
    void maintainHeap();
    // int initializeArrays();

    // given functions from project description
    void findContestant(int, FILE *);
    void insertContestant(int, int, FILE *);
    void eliminateWeakest(FILE *);
    void earnPoints(int, int, FILE *);
    void losePoints(int, int, FILE *);
    void showContestants(FILE *);
    void showHandles(FILE *);
    void showLocation(int, FILE *);
    void crownWinner(FILE *);
};
#endif
