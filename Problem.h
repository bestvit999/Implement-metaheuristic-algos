#include <vector>
#include <iostream>
#include <string>
#include "SearchAlgo.h"
#include "fetchfile.h"

using namespace std;

class Problem
{
public:
    void exec(SearchAlgo);
};

class Knapsack : Problem
{
private:
    int capacity;
    vector<int> values;
    vector<int> weights;
    vector<int> opt_sol;

public:
    Knapsack(string path_to_folder)
    {
        vector<string> files = {"/capacity.dat", "/value.dat", "/weight.dat", "/opt_result.dat"};
        capacity = getfile(path_to_folder + files[0])[0];
        values = getfile(path_to_folder + files[1]);
        weights = getfile(path_to_folder + files[2]);
        opt_sol = getfile(path_to_folder + files[3]);
    }

    void exec(SearchAlgo algo){
        
    }
};