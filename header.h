#pragma once

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <vector>

using namespace std;

typedef vector<int> solution;
typedef vector<solution> population;

//=====================================//
//         Algorithm Section          //
//===================================//
#ifndef ALGO_H
#define ALGO_H
class Prob;
class Knap;
class Algo
{
public:
    /* overloading here */
    void run(Prob *prob_prt){};
    virtual void run(Knap *prob_ptr) = 0;

public:
    solution mutate(solution origin, int random_rumber);  // T
    double fitness(solution candidate);                   // E
    void determine(solution candidate, solution &origin); // D
};
#endif

//=====================================//
//           Algo TS Section          //
//===================================//
#ifndef ALGOTS_H
#define ALGOTS_H
class Prob;
class Knap;
class Tabu;

class TS : public Algo
{
private:
    Tabu *tabu;
    int random_range;
    Knap *knap_ptr;
public:
    TS(Tabu *tabu);

public:
    void run(Knap *knap_ptr);

public:
    solution mutate(solution origin);   // T
    double fitness(solution candidate);                   // E
    double fitness_Weight(solution candidate);            // E
    void determine(solution candidate, solution &origin); // D
public:
    void setRandomRange(int random_range);
    int getRandomRange();
};

class Tabu
{
private:
    vector<solution> tabuList;
    int maxsize;
public:
    Tabu(int tabusize);
public:
    void enqueue(solution candidate);
    void dequeue();
    int is_member(solution candidate);
    int size();
    int getMaxsize();
};
#endif

//=====================================//
//           Algo SA Section          //
//===================================//
#ifndef ALGOSA_H
#define ALGOSA_H
class Prob;
class Knap;
class SA : public Algo
{
private:
    double temperature;
    double alpha;
    Knap *knap_ptr;
    int random_range; // for mutate
public:
    SA(double temperature, double alpha);

public:
    void run(Prob *prob_ptr);
    void run(Knap *prob_ptr); /* 01-kanp with SA */
public:
    solution mutate(solution origin, int random_range);   // T
    double fitness(solution candidate);                   // E
    double fitness_Weight(solution candidate);            // E
    void determine(solution candidate, solution &origin); // D
    double probability(solution candidate, solution origin);

public:
    int getRandomRange();
    void setRandomRange(int random_range);
};
#endif

//=====================================//
//           Algo GA Section          //
//===================================//
#ifndef ALGOGA_H
#define ALGOGA_H
class GA : public Algo
{
private:
    int popsize;
    Knap *knap_ptr;
    int random_range; // for mutate
public:
    GA(int popsize);

public:
    void run(Knap *prob_ptr);

public:
    solution mutate(solution origin);                 // T
    double fitness(solution individual);              // E
    double fitness_weight(solution individaul);       // E
    void determine(population pop, solution &origin); // D
public:
    population init(int popsize);                         // init the base-generation
    vector<solution> selectParent(population population); // select two better parents in the generation
    vector<double> cumulateSum(population population);    // select parents scheme, in order to increase Diversity
    solution rouletteWheel(population pop, vector<double> cumsum);
    int partition(population arr, int front, int end);
    void quickSort(population arr, int front, int end);
    double summation(population population);
    vector<solution> recombination(vector<solution> parents); // crossingover the genes
    void crossingover(solution &chromosome1, solution &chromesome2, int index);

public:
    int getRandomRange();
    void setRandomRange(int random_range);
};
#endif

//=====================================//
//           Problem Section          //
//===================================//
#ifndef PROB_H
#define PROB_H
class Prob
{
public:
    virtual void run(Algo *algo_ptr) = 0;
};
#endif

//=====================================//
//         Prob-Knap Section          //
//===================================//
#ifndef PROBKNAP_H
#define PROBKNAP_H
class Knap : public Prob
{
public:
    Knap(string path_to_folder);
    int iterations;

private:
    int capacity;
    vector<int> values;
    vector<int> weihgts;
    vector<int> opt;
    solution candidate;

public:
    void run(Algo *algo_ptr);
    void showAllmember();
    void showCandidate();
    int getCapacity();
    vector<int> getValues();
    vector<int> getWeihgts();
    vector<int> getOpt();
    solution getCandidate();
    void setCandidate(solution candidate);
    void setIteration(int iter);
};
#endif

// local function
vector<int> readfile(string);
void showSolution(solution candidate);
void showPopulation(population population);
