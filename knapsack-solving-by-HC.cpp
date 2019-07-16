#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <fstream>

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
vector<vector<int>> dataframe = {capacity, values, weights, opt_result};

/* calculate the tweak duration */
double _durations = 0.0;
auto start = chrono::system_clock::now();

// for output file
ofstream outFile;

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

    // fetch knapsack data from giving dataset folder
    string path_to_dataset_folder = base_path + datasetFolder;
    fetchFile(path_to_dataset_folder);

    // default is all zero, it means that no item be selected
    vector<int> itemSelected = initialization();
    vector<int> tmp;

    string path_to_output_folder = "data//output//";
    string output_file = path_to_output_folder + "knapsack-hc.dat";

    outFile.open(output_file);

    // count iterations
    int iterations = 0;

    /* while iterations as known as SELECTION STAGE  */
    while (_durations < durations && !isOpt_result(tmp))
    {
        iterations++;

        /* btw, we also can apply some aggrasive approach here */
        /* by multi-tweak at the same time, and pick up the highest eval(itemSelected) one */
        tmp = tweak(itemSelected, range);

        int tmp_value = evaluate_value(tmp);
        int best_value = evaluate_value(itemSelected);
        // find some tweak is better than older, then update it
        if (tmp_value > best_value && evaluate_weight(itemSelected) <= dataframe[0][0])
        {
            itemSelected = tmp;
            for (int i = 0; i < itemSelected.size(); i++)
            {
                outFile << itemSelected[i];
                cout << itemSelected[i];
            }
            double cp = double(evaluate_value(itemSelected)) / double(evaluate_weight(itemSelected));
            cout << ", value is : " << evaluate_value(itemSelected) << ", weight is : " << evaluate_weight(itemSelected) << ", cp is : " << cp << endl;
            outFile << ' ' << evaluate_value(itemSelected) << ' ' << iterations << ' ' << cp << '\n';
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
    int len = tmp.size();

    // store the eval(origin) value, for detect replace bitstring or not
    int value_origin = evaluate_value(origin);

    // here we apply random skill to portion of bitstring
    for (int i = 0; i < range; i++)
    {
        int index = rand() % len;
        tmp[index] = rand() % 2; // cycled affect portion of bitstring
    }
    int value_tmp = evaluate_value(tmp); // then we got eval(tmp), so we can detect which is better

    if (value_tmp > value_origin && evaluate_weight(tmp) <= dataframe[0][0])
    {
        // use for output the durations for Tweak process
        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;

        cout << "> Tweak successed, duration :" << durations.count() << endl;
        _durations = durations.count();

        return tmp;
    }
    else
    {
        // keep the origin bitstring
        return origin;
    }
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
        return 1;
    }
    else
    {
        return 0;
    }
}