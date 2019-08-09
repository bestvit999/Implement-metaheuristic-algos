#include "header.h"
#include <numeric>
#include <algorithm>

using namespace std;

void showResult(vector<int> iterList);

int main(int argc, char *argv[])
{
    srand(time(0));

    /* assign the arguments */
    string path_to_folder = argv[1];
    int runs = atoi(argv[2]);
    int tabusize = atoi(argv[3]);

    int random_range = 5; // default 5

    /* construct the Prob and SearchAlgo object */
    Knap *knap_ptr = new Knap(path_to_folder);
    Tabu *tabu = new Tabu(tabusize);
    TS *ts_ptr = new TS(tabu);
    ts_ptr->setRandomRange(random_range);

    /* show prob information */
    cout << "==Knap-TS==" << endl;
    knap_ptr->showAllmember(); // list knapsack information

    /* do several times */
    vector<int> iterList;
    for (int i = 0; i < runs; i++)
    {
        knap_ptr->run(ts_ptr);
        iterList.push_back(knap_ptr->iterations);
    }

    showResult(iterList);
    showSolution(knap_ptr->getBest());
    cout << "\n===========" << endl;

    /* Remark : remember to delete useless ptr */
    delete ts_ptr;
    delete knap_ptr;
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
    string command1 = "sed -i 's/$mints/";
    string command2 = "/g' figure.plt";
    string command = command1 + to_string(minIndex) + command2;
    char const *ptr = command.c_str();
    system(ptr);
}