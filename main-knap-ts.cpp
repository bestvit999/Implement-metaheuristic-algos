#include "header.h"
#include <numeric>
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
    knap_ptr->showAllmember(); // list knapsack information
    knap_ptr->showCandidate();
    cout << "-- -- -- --" << endl;

    /* do several times */
    vector<int> iterList;
    for (int i = 0; i < runs; i++)
    {
        knap_ptr->run(ts_ptr);
        cout << "=" << endl;

        iterList.push_back(knap_ptr->iterations);
    }

    showResult(iterList);

    /* Remark : remember to delete useless ptr */
    delete ts_ptr;
    delete knap_ptr;
}

void showResult(vector<int> iterList)
{

    int max = *max_element(iterList.begin(), iterList.end()); // `*` before max_element that is because ´max_element´ returns an iterator
    int min = *min_element(iterList.begin(), iterList.end());
    double avg = accumulate(iterList.begin(), iterList.end(), 0) / iterList.size();

    cout << "max : " << max << endl;
    cout << "min : " << min << endl;
    cout << "avg : " << avg << endl;
}