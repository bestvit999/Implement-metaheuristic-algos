#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <fstream>

using namespace std;


vector<bool> initialization(vector<vector<int>> knapsack_data); // *init* each item's value and weight from giving dataset
vector<bool> tweak(vector<bool> origin,int capacity, int range); // generate the next token, a.k.a. *Transportation*

/* fetch the .dat file (dataset) */
vector<vector<int>> getLines(string file_path);
void getValue_n_Weight(vector<vector<int>> knapsack_data);
vector<int> split(string line, string delimeter);

/* assess the token, a.k.a. Evaluate */
int evaluate_value(vector<bool> itemselection);
int evaluate_weight(vector<bool> itemselection);

/* global variable */
vector<int> values;
vector<int> weights;

/* calculate the tweak duration */
double _durations = 0.0;
auto start = chrono::system_clock::now();

// for output file
ofstream outFile;

int main(int argc,char * argv[]){
    srand(time(0));
    // read all arguments to *all_args*
    vector<string> all_args;
    all_args.assign(argv+1, argv+argc);

    // path to dataset
    string base_path = "data//";
    string file_name = all_args[0];
    
    int capacity = stoi(all_args[1]); // knapsack capacity
    int durations = stoi(all_args[2]); // constraint variable
    int range = stoi(all_args[3]); // random size

    // fetch knapsack data from .dat file (dataset)
    vector<vector<int>> knapsack_data = getLines(base_path.append(file_name));
    getValue_n_Weight(knapsack_data); // and assign it to <global variable>

    // default is all zero, it means that no item be selected
    vector<bool> itemSelected = initialization(knapsack_data);
    vector<bool> tmp;

    outFile.open("data//dataset-knapsack.dat");

    /* while iterations as known as SELECTION STAGE  */ 
    while (_durations < durations){
        /* btw, we also can apply some aggrasive approach here */
        /* by multi-tweak at the same time, and pick up the highest eval(itemSelected) one */
        tmp = tweak(itemSelected,capacity,range);

        int tmp_value = evaluate_value(tmp);
        int best_value = evaluate_value(itemSelected);
        // find some tweak is better than older, then update it
        if (tmp_value > best_value && evaluate_weight(itemSelected) <= capacity){
            itemSelected = tmp;
            for (int i = 0; i < itemSelected.size() ; i ++){
                outFile << itemSelected[i];
                cout << itemSelected[i];
            }
            double cp =  double(evaluate_value(itemSelected)) / double(evaluate_weight(itemSelected));
            cout << ", value is : " << evaluate_value(itemSelected) << ", weight is : " << evaluate_weight(itemSelected) << ", cp is : " << cp << endl;
            outFile << ' ' << evaluate_value(itemSelected) << ' ' << cp << '\n';
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
vector<bool> initialization(vector<vector<int>> knapsack_data){
    vector<bool> itemSelected;
    for (int i = 0; i < knapsack_data.size();i++){
        itemSelected.push_back(0); // default select none
    }
    return itemSelected;
}

/* the most important part */ 
/* here we use the random search skill, it will tweak some portion of bitstring */
vector<bool> tweak(vector<bool> origin,int capacity, int range){
    vector<bool> tmp = origin; // copy the origin bitstring, use for tweaking
    int len = tmp.size();

    // store the eval(origin) value, for detect replace bitstring or not
    int value_origin = evaluate_value(origin);

    // here we apply random skill to portion of bitstring
    for (int i = 0; i < range; i++){
        int index = rand() % len;
        tmp[index] = rand() % 2; // cycled affect portion of bitstring
    }
    int value_tmp = evaluate_value(tmp); // then we got eval(tmp), so we can detect which is better


    if (value_tmp > value_origin && evaluate_weight(tmp) <= capacity){
        // use for output the durations for Tweak process
        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;

        cout << "> Tweak successed, duration :" << durations.count() << endl;
        _durations =  durations.count();

        return tmp;
    }else{
        // keep the origin bitstring
        return origin;
    }
}

int evaluate_value(vector<bool> itemselection){
    int totalValue = 0;
    for (int i = 0;i < itemselection.size();i++){
        if (itemselection[i]){
            totalValue += values[i];
        }
    }        
    return totalValue;
}

int evaluate_weight(vector<bool> itemselection){
    int totalWeight = 0;
    for (int i = 0;i < itemselection.size();i++){
        if (itemselection[i]){
            totalWeight += weights[i];
        }
    }
        
    return totalWeight;

}

vector<vector<int>> getLines(string file_path){
    vector<vector<int>> df;

    string line;
    string delimeter = " ";
    ifstream myfile(file_path);
    int i = 0;
    while(getline(myfile,line)){
        df.push_back(split(line," "));
    }
    return df;
}

void getValue_n_Weight(vector<vector<int>> knapsack_data){
    for (int i = 0; i < knapsack_data.size();i++){
        values.push_back(knapsack_data[i][0]);
        weights.push_back(knapsack_data[i][1]);
    }
}

vector<int> split(string line, string delimeter){
    vector<int> row;
    while (line.find(delimeter) != string::npos){
        row.push_back(stoi(line.substr(0,line.find(delimeter))));
        line.erase(0,line.find(delimeter)+1);
    }
    row.push_back(stoi(line));
    return row;
}
