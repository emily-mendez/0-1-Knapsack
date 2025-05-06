#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

struct Item {
    int weight;
    int profit;
    int pwratio;
    Item(int w, int p) : weight(w), profit(p), pwratio(p/w) {}
};

struct ProblemSet {
    int numItems;
    int capacity;
    vector<Item> items;
    int greedy1Max = 0;
    int maxProfit = 0;
};

class Algorithms {
    public:
        void greedy1();
        void greedy2();
        void backtracking(int i, int profit, int weight, ProblemSet& currProb);
        bool promising(int i, int profit, int weight, ProblemSet& currProb);
        float KWF2(int i, int weight, int profit, ProblemSet& currProb);
        vector<ProblemSet> problemSets;
        bool isGreedy1 = false;
        bool isGreedy2 = false;
};

#endif