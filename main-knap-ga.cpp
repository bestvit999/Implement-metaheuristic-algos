#include "header.h"
#include <numeric>
#include <algorithm>

void showResult(vector<int> iterList);

int main(int argc, char *argv[])
{
    /* assign the arguments */
    string path_to_folder = argv[1];
    int runs = atoi(argv[2]);
    int popsize = atoi(argv[3]);
    int smethod = atoi(argv[4]); // 0: tournament selection, 1: roulette wheel

    /* construct the Prob and SearchAlgo object */
    Knap *knap_ptr = new Knap(path_to_folder);
    GA *ga_ptr = new GA(popsize);
    ga_ptr->setSelectionMethod(smethod); // 0: tournament selection, 1: roulette wheel

    /* show prob information */
    cout << "==Knap-GA==" << endl;
    knap_ptr->showAllmember();

    /* do several times */
    vector<int> iterList;
    for (int i = 0; i < runs; i++)
    {
        knap_ptr->run(ga_ptr);
        iterList.push_back(knap_ptr->iterations);
    }

    showResult(iterList);
    showSolution(knap_ptr->getBest());
    cout << "\n===========" << endl;

    /* Remark : remember to delete useless ptr */
    delete knap_ptr;
    delete ga_ptr;
}

void showResult(vector<int> iterList)
{
    int maxIndex = max_element(iterList.begin(), iterList.end()) - iterList.begin() + 1;
    int minIndex = min_element(iterList.begin(), iterList.end()) - iterList.begin() + 1;

    int max = *max_element(iterList.begin(), iterList.end()); // `*` before max_element that is because ´max_element´ returns an iterator
    int min = *min_element(iterList.begin(), iterList.end());
    double avg = accumulate(iterList.begin(), iterList.end(), 0) / iterList.size();

    cout << "max : " << max << ", max index : " << maxIndex << endl;
    cout << "min : " << min << ", min index : " << minIndex << endl;
    cout << "avg : " << avg << endl;

    // for gnuplot the <index of output data>
    string command1 = "sed -i 's/$minga/";
    string command2 = "/g' figure.plt";
    string command = command1 + to_string(minIndex) + command2;
    char const *ptr = command.c_str();
    system(ptr);
}