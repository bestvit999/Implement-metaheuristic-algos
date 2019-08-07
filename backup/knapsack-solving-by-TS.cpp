#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

vector<int> initialization();                     // *init* each item's value and weight from giving dataset
vector<int> tweak(vector<int> origin, int range); // generate the next token, a.k.a. *Transportation*

/* fetch the .dat file (dataset) */
void fetchFile(string path_to_input_folder);

/* assess the token, a.k.a. Evaluate */
int evaluate_value(vector<int> itemselection);
int evaluate_weight(vector<int> itemselection);

/* terminal by comparing <itemSelected> and <opt_result> */
int isOpt_result(vector<int> itemSelected);

/* global variable */
vector<int> capacity;
vector<int> values;
vector<int> weights;
vector<int> opt_result;
// 0->capacity,1->values,2->weights,3->opt_result
// each type of dataframe's element is a vector<int>
vector<vector<int>> dataframe = {capacity, values, weights, opt_result};

/* calculate the tweak duration */
double _durations = 0.0;
auto start = chrono::system_clock::now();

// count iterations
int iterations = 0;

// for output file
ofstream outFile;

/* Tabu List */
vector<vector<int>> tabuList; // implement as FIFO queue
class Tabu
{
public:
    void enqueue(vector<int> tmp)
    {
        tabuList.push_back(tmp);
    }

    void dequeue()
    {
        tabuList.erase(tabuList.begin());
    }
    int is_member(vector<int> tmp)
    {
        for (int i = 0; i < tabuList.size(); i++)
        {
            if (tabuList[i] == tmp)
            {
                return 1;
            }
        }
        return 0;
    }
    int size()
    {
        return tabuList.size();
    }
};

int main(int argc, char *argv[])
{
    srand(time(0));
    // read all arguments to *all_args*
    vector<string> all_args;
    all_args.assign(argv + 1, argv + argc);

    // path to dataset
    string base_path = "data//input//";
    string datasetFolder = all_args[0];

    int durations = stoi(all_args[1]); // constraint variable
    int range = stoi(all_args[2]);     // random size
    int MAXSIZEofTL = stoi(all_args[3]);

    // fetch knapsack data from giving dataset folder
    string path_to_dataset_folder = base_path + datasetFolder;
    fetchFile(path_to_dataset_folder);

    // default is all zero, it means that no item be selected
    vector<int> itemSelected = initialization(); // S
    vector<int> best = itemSelected;             // Best
    vector<int> tmp;                             // R
    vector<int> ttmp;                            // W

    string path_to_output_folder = "data//output//";
    string output_file = path_to_output_folder + "knapsack-ts.dat";

    outFile.open(output_file);

    // count for iterations
    int iterations = 0;

    // tabuList
    Tabu tabu;
    /* while iterations as known as SELECTION STAGE  */
    while (_durations < durations && !isOpt_result(best))
    {
        iterations++;
        if (tabu.size() >= MAXSIZEofTL)
        {
            tabu.dequeue();
        }

        // candidate
        tmp = tweak(itemSelected, range);

        // find the better candidate in neighborhood from <S>
        // at the same time, exclude the neighbor that in <Tabu>
        for (int i = 0; i < range; i++)
        {
            ttmp = tweak(itemSelected, range);
            if (!tabu.is_member(ttmp) && (evaluate_value(ttmp) > evaluate_value(tmp) || tabu.is_member(tmp)) && evaluate_weight(ttmp) <= dataframe[0][0])
            {
                tmp = ttmp;
            }
        }

        if (!tabu.is_member(tmp) && evaluate_weight(tmp) <= dataframe[0][0])
        {
            itemSelected = tmp;
            tabu.enqueue(tmp);
        }

        if (evaluate_value(itemSelected) > evaluate_value(best))
        {
            best = itemSelected;

            for (int i = 0;i < best.size();i++){
                cout << best[i];
                outFile << best[i];
            }
            cout << ", value :" << evaluate_value(best) << ", weight :" << evaluate_weight(best) << ", tabu size : " << tabu.size() << ", iteration : " << iterations << endl;
            outFile << ' ' << evaluate_value(best) << ' ' << iterations << endl;
        }

        // use for controlling process duration limit
        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;
        _durations = durations.count();
    }
    outFile.close();
}

// init the bitstring, default is all zero
// btw, it also can be set in random case
vector<int> initialization()
{
    vector<int> itemSelected;
    for (int i = 0; i < dataframe[1].size(); i++)
    {
        itemSelected.push_back(0); // default select none
    }
    return itemSelected;
}

/* the most important part */
/* here we use the random search skill, it will tweak some portion of bitstring */
vector<int> tweak(vector<int> origin, int range)
{
    vector<int> tmp = origin; // copy the origin bitstring, use for tweaking
    // here we apply random skill to portion of bitstring
    for (int i = 0; i < range; i++)
    {
        int index = rand() % tmp.size();
        tmp[index] = rand() % 2; // cycled affect portion of bitstring
    }

    iterations++;

    return tmp;
}

int evaluate_value(vector<int> itemselection)
{
    int totalValue = 0;
    for (int i = 0; i < itemselection.size(); i++)
    {
        if (itemselection[i])
        {
            totalValue += dataframe[1][i];
        }
    }
    return totalValue;
}

int evaluate_weight(vector<int> itemselection)
{
    int totalWeight = 0;
    for (int i = 0; i < itemselection.size(); i++)
    {
        if (itemselection[i])
        {
            totalWeight += dataframe[2][i];
        }
    }

    return totalWeight;
}

void fetchFile(string path_to_input_folder)
{
    string line;

    // path configuration
    string path_to_capacity = path_to_input_folder + "//capacity.dat";
    string path_to_value = path_to_input_folder + "//value.dat";
    string path_to_weight = path_to_input_folder + "//weight.dat";
    string path_to_opt_result = path_to_input_folder + "//opt_result.dat";

    vector<string> args = {path_to_capacity, path_to_value, path_to_weight, path_to_opt_result};

    for (int i = 0; i < args.size(); i++)
    {
        ifstream inputFile(args[i]);
        while (getline(inputFile, line))
        {
            dataframe[i].push_back(stoi(line));
        }
    }
}

int isOpt_result(vector<int> itemSelected)
{
    if (dataframe[3] == itemSelected)
    {
        cout << "optima found!" << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}