#include "Algorithms.h"
using namespace std;

ofstream outfile;

int main(int argc, char* argv[]) {
    Algorithms result;
    ifstream infile(argv[1]);
    outfile.open(argv[2]);
    int num, cap;

    while(infile >> num >> cap) {
        ProblemSet problem;
        problem.capacity = cap;
        problem.numItems = num;
        for(int i = 0; i < num; i++) {
            int weight, profit;
            infile >> weight >> profit;
            Item item = Item(weight, profit);
            problem.items.push_back(item);
        }
        std::sort(problem.items.begin(), problem.items.end(), [](const Item &a, const Item &b) {
            return a.pwratio > b.pwratio;
        });
        result.problemSets.push_back(problem);
    }

    int algType = atoi(argv[3]);

    if(algType == 0) {
        result.isGreedy1 = true;
        result.greedy1();
    } else if(algType == 1) {
        result.isGreedy2 = true;
        result.greedy1();
        result.greedy2();
    } else if(algType == 2) {
        result.greedy1();
        result.greedy2();
        for(int i = 0; i < result.problemSets.size(); i++) {
            auto start = std::chrono::high_resolution_clock::now();
            result.backtracking(-1, 0, 0, result.problemSets[i]);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            outfile << result.problemSets[i].numItems << " " << result.problemSets[i].maxProfit << " " << duration.count() << " ms" << endl;
        }
    } else {
        cout << "Invalid arg 3, should be of the form <0/1/2>" << endl;
    }
    
}