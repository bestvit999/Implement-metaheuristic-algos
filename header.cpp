#include "header.h"

// local function
vector<int> readfile(string path_to_file)
{
    std::ifstream input;
    string line;
    vector<int> output;

    input.open(path_to_file);
    while (!input.eof())
    {
        input >> line;
        output.push_back(stoi(line));
    }
    input.close();
    return output;
}

void showSolution(solution candidate)
{
    cout << "candidate : ";
    for (int i = 0; i < candidate.size(); i++)
    {
        cout << candidate[i] << ' ';
    }
};

void showPopulation(population population)
{
    for (int i = 0; i < population.size(); i++)
    {
        for (int j = 0; j < population[i].size(); j++)
        {
            cout << population[i][j];
        }
        cout << ' ';
    }
}