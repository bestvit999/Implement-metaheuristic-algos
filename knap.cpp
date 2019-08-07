#include "header.h"

// implementation of Knap
Knap::Knap(string path_to_folder)
{

    string path_to_file;
    path_to_file = path_to_folder + "/p01_c.txt";
    this->capacity = readfile(path_to_file)[0];

    path_to_file = path_to_folder + "/p01_p.txt";
    this->values = readfile(path_to_file);

    path_to_file = path_to_folder + "/p01_w.txt";
    this->weihgts = readfile(path_to_file);

    path_to_file = path_to_folder + "/p01_s.txt";
    this->opt = readfile(path_to_file);

    for (int i = 0; i < values.size(); i++)
    {
        int gene = 0; // here apply all zero at initial
        this->candidate.push_back(gene);
    }
}

void Knap::run(Algo *algo_ptr)
{
    algo_ptr->run(this);
}

void Knap::showAllmember()
{
    cout << "capacity : " << capacity << endl;
    cout << "value : ";
    for (int i = 0; i < values.size(); i++)
    {
        cout << values[i] << ' ';
    }
    cout << '\n';
    cout << "weight : ";
    for (int i = 0; i < weihgts.size(); i++)
    {
        cout << weihgts[i] << ' ';
    }
    cout << '\n';
    cout << "opt : ";
    for (int i = 0; i < opt.size(); i++)
    {
        cout << opt[i] << ' ';
    }
    cout << '\n';
}

void Knap::showCandidate()
{
    cout << "init candidate : ";
    for (int i = 0; i < candidate.size(); i++)
    {
        cout << candidate[i] << ' ';
    }
    cout << '\n';
}

/* 01-knap info getter and setter */
int Knap::getCapacity() { return capacity; }
vector<int> Knap::getValues() { return values; }
vector<int> Knap::getWeihgts() { return weihgts; }
vector<int> Knap::getOpt() { return opt; }
solution Knap::getCandidate() { return candidate; }
void Knap::setCandidate(solution _candidate) { candidate = _candidate; }
void Knap::setIteration(int iter) { iterations = iter; }
