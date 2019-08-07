#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

/* public attributes */
// store the knapsack information
vector<int> capacity;
vector<int> values;
vector<int> weights;
vector<int> opt_result;
vector<vector<int>> dataframe = {capacity, values, weights, opt_result};
int popsum = 0;

/* methods */
// fetch knapsack info from file to <dataframe>
void fetchFile(string path_to_input_folder);
int isOpt_result(vector<int> itemSelected);
//// init ////
vector<vector<int>> initialization(int populationSize);
int partition(vector<vector<int>> arr, int front, int end);
void quickSort(vector<vector<int>> arr, int front, int end);
//// selection ////
vector<int> selectParent(vector<vector<int>> population);
int summation(vector<vector<int>> population);
int evaluate_value(vector<int> individual);
int evaluate_weight(vector<int> individual);
vector<double> rouletteWheel(vector<vector<int>> population);
//// recombination ////
vector<vector<int>> recombination(vector<int> parent1,vector<int> parent2);
void crossingover(vector<int> & a, vector<int> & b, int index);
//// mutate /////
vector<int> mutate(vector<int> individual);
void bitfilp(vector<int> & individual, int index);

int main(int argc, char *argv[])
{   
    srand(time(NULL));

    fetchFile("data//input//dataset3");
    vector<vector<int>> population = initialization(20); // popsize = 20;
    vector<int> best; // best individual
    int generations = 0;

    vector<vector<int>> cpopulation; // child generation population
    vector<vector<int>> childs;
    vector<int> p1;
    vector<int> p2;
    vector<int> c1;
    vector<int> c2;


    while(!isOpt_result(best)){

        for(int i = 0;i < 20;i++){
            // for (int j = 0;j < population[i].size();j++){
            //     cout << population[i][j];
            // }
            if (evaluate_value(population[i]) > evaluate_value(best) && evaluate_weight(population[i]) <= dataframe[0][0]){
                best = population[i];
                // for (int i = 0;i < best.size();i++){
                //     cout << best[i];
                // }
                // cout << ' ' << evaluate_value(best) << ' ' << generations << endl;
            }
            cout << ' ';
        }
        cout << endl;

        for (int i = 0;i < 10;i++){
            /* A. SELECTION */
            // pick two individual as parent from <population>
            p1 = selectParent(population);
            p2 = selectParent(population);

            /* B. recombination */
            // here we apply the *Uniform Crossover*
            childs = recombination(p1,p2);
            c1 = childs[0];
            c2 = childs[1];

            /* C. mutation */
            // here we apply the *Bit-Flip Mutation*
            
            cpopulation.push_back(mutate(c1));
            cpopulation.push_back(mutate(c2));
        }

        population = cpopulation; // replace the old population

        cout << '\r' << generations;
        generations++;

        cpopulation.clear();
    }
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
            dataframe[i].push_back(stoi(line)); // segmentation fault
        }
    }
}

int isOpt_result(vector<int> itemSelected)
{
    if (dataframe[3] == itemSelected)
    {
        cout << "optima found!"<< endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

/* INITIALIZATION */

vector<vector<int>> initialization(int populationSize)
{
    vector<vector<int>> population;
    for (int i = 0; i < populationSize; i++)
    {
        vector<int> individual;
        for (int j = 0; j < dataframe[1].size(); j++)
        {
            individual.push_back(rand() % 2);
        }
        population.push_back(individual);
    }
    popsum = summation(population);
    return population;
}

int partition(vector<vector<int>> arr, int front, int end)
{
    int pivot = evaluate_value(arr[end]);
    int i = front - 1;
    for (int j = front; j < end; j++)
    {
        if (evaluate_value(arr[j]) > pivot)
        {
            i++;
            arr[i].swap(arr[j]);
        }
    }
    i   ++;
    arr[i].swap(arr[end]);
    return i;
}

void quickSort(vector<vector<int>> arr, int front, int end)
{
    if (front < end)
    {
        int pivot = partition(arr, front, end);
        quickSort(arr, front, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

/* SELECTION */

// implement the *Roulette Wheel* as SELECTION, and there are several stages to do
// 1. normalize the Fitness Value (NF)
// 2. cumulated the NF (CumSum)
// 3. set r = random number between [0,1], IF r is in section of Roulette Wheel of individual, THEN pick the specific individual as parent
vector<int> selectParent(vector<vector<int>> population)
{
    quickSort(population, 0, population.size() - 1); // before started, need to sort the population
    vector<int> parent;
    vector<double> cumulatedSum = rouletteWheel(population); // CumSum

    double r = double(rand()) / RAND_MAX;

    // cout << r << " : ";

    for(int i = 0;i < cumulatedSum.size();i++){
        if (r >= cumulatedSum[i])
        {
            if (i==0){
                parent = population[i];
            }else{
                parent = population[i-1];
            }
            // cout << i-1 << " ";
            break;
        }
    }
    return parent;
}

int summation(vector<vector<int>> population)
{
    int sum = 0;
    for (int i = 0; i < population.size(); i++)
    {
        sum += evaluate_value(population[i]);
    }
    return sum;
}

int evaluate_value(vector<int> individual)
{
    int totalValue = 0;
    for (int i = 0; i < individual.size(); i++)
    {
        if (individual[i])
        {
            totalValue += dataframe[1][i];
        }
    }
    return totalValue;
}

int evaluate_weight(vector<int> individual)
{
    int totalWeight = 0;
    for (int i = 0; i < individual.size(); i++)
    {
        if (individual[i])
        {
            totalWeight += dataframe[2][i];
        }
    }

    return totalWeight;
}

vector<double> rouletteWheel(vector<vector<int>> population)
{
    vector<double> cumulatedSum;
    for (int i = 0; i < population.size(); i++)
    {
        double cumulated = 0.0;
        for (int j = i; j < population.size(); j++)
        {
            cumulated += double(evaluate_value(population[j])) / double(popsum);
        }
        cumulatedSum.push_back(cumulated);
    }
    cumulatedSum.push_back(0.0);
    return cumulatedSum;
}

/* RECOMBINATION */
// here we apply *uniform crossover*
vector<vector<int>> recombination(vector<int> parent1,vector<int> parent2){
    vector<vector<int>> childs;
    vector<int> c1 = parent1;
    vector<int> c2 = parent2;

    // cout << c1.size() << " " << c2.size() << endl;

    double p = 1.0 / double(parent1.size()); // often p is set to 1/length, or p <= 0.5

    for (int i = 0;i < c1.size();i++){
        double randnum = double(rand()) / RAND_MAX; // rand a number between [0,1]
        if (p >= randnum){
            crossingover(c1,c2,i);
        }
    }

    childs.push_back(c1);
    childs.push_back(c2);
    return childs;
}

void crossingover(vector<int> & a, vector<int> & b, int index){
    int tmp = a[index];
    a[index] = b[index];
    b[index] = tmp;
}

/* MUTATION */
// here we apply *Bit-Flip Mutation*
vector<int> mutate(vector<int> individual){
    vector<int> tmp = individual;
    double p = 1.0 / double(tmp.size()); // often p is 1/length, or p <= 0.5

    for (int i = 0;i < tmp.size();i++){
        double randnum = double(rand()) / RAND_MAX; // rand a number between [0,1]
        if (p >= randnum){
            bitfilp(tmp,i);
        }
    }

    return tmp;
}

void bitfilp(vector<int> & individual, int index){
    if (individual[index] == 0){
        individual[index] = 1;
    }else{
        individual[index] = 0;
    }
}