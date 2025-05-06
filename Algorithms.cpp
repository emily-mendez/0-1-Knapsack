#include "Algorithms.h"
#include <thread>
using namespace std;

extern ofstream outfile;

void Algorithms::greedy1() {
    for(int i = 0; i < problemSets.size(); i++) {
        auto start = std::chrono::high_resolution_clock::now();
        int maxProfit = 0;
        int currWeight = 0;
        for(int j = 0; j < problemSets[i].items.size(); j++) {
            if(currWeight + problemSets[i].items[j].weight <= problemSets[i].capacity) {
                maxProfit += problemSets[i].items[j].profit;
                currWeight += problemSets[i].items[j].weight;
            }
        }
        problemSets[i].greedy1Max = maxProfit;
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if(isGreedy1) outfile << problemSets[i].numItems << " " << maxProfit << " " << duration.count() << " ms" << endl;
    }
}

void Algorithms::greedy2() {
    for(int i = 0; i < problemSets.size(); i++) {
        auto start = std::chrono::high_resolution_clock::now();
        bool found = false;
        for(int j = 0; j < problemSets[i].items.size(); j++) {
            if(problemSets[i].items[j].profit > problemSets[i].greedy1Max && problemSets[i].items[j].weight <= problemSets[i].capacity) {
                problemSets[i].maxProfit = problemSets[i].items[j].profit;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                if(isGreedy2) outfile << problemSets[i].numItems << " " << problemSets[i].items[j].profit << " " << duration.count() << " ms" << endl;
                found = true;
                break;
            }
        }
        if(!found) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            if(isGreedy2) outfile << problemSets[i].numItems << " " << problemSets[i].greedy1Max << " " << duration.count() << " ms" << endl;
            problemSets[i].maxProfit = problemSets[i].greedy1Max;
        }
    }
}

void Algorithms::backtracking(int i, int profit, int weight, ProblemSet& currProb) {
    if(weight <= currProb.capacity && profit > currProb.maxProfit) {
        currProb.maxProfit = profit;
    }
    //cout << weight << " " << currProb.capacity << " " << currProb.maxProfit << " " << currProb.numItems << endl;
    if(promising(i, profit, weight, currProb)) {
        backtracking(i + 1, profit + currProb.items[i + 1].profit, weight + currProb.items[i + 1].weight, currProb);
        backtracking(i + 1, profit, weight, currProb);
    }
}

bool Algorithms::promising(int i, int profit, int weight, ProblemSet& currProb) {
    if(weight >= currProb.capacity) return false;
    float bound = KWF2(i + 1, weight, profit, currProb);
    //cout << bound << endl;
    return (bound > currProb.maxProfit);
}

float Algorithms::KWF2(int i, int weight, int profit, ProblemSet& currProb) {
    float bound = profit;
    //cout << "i : " << i << " numItems : " << currProb.numItems << endl;
    while((weight < currProb.capacity) && (i < currProb.numItems)) {
        if(weight + currProb.items[i].weight <= currProb.capacity) {
            weight += currProb.items[i].weight;
            bound += currProb.items[i].profit;
        } else {
            float fraction = (float)(currProb.capacity - weight) / currProb.items[i].weight;
            //cout << currProb.capacity << " " << weight << " " << currProb.items[i].weight << endl;
            //cout << fraction << endl;
            weight = currProb.capacity;
            bound += currProb.items[i].profit * fraction;
            //cout << "here" << endl;
        }
        i++;
    }
    return bound;
}