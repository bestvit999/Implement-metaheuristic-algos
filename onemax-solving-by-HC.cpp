#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <fstream>

using namespace std;

// init the bitstring from giving bit size
vector<bool> initialization(int bits);
// find next candidate bit string to be evaluated
vector<bool> tweak(vector<bool> origin, int range);
// evaluate the number of one in bit string
int eval(vector<bool> bitset);
// evaluate the number of one in bit string in some particular range
int eval_in_range(vector<bool> tmp, int begin, int range);

double _durations = 0.0;

// for calculate the tweak duration
auto start = chrono::system_clock::now();
ofstream outFile;

int main(int argc,char * argv[]){
    srand(time(0)); // set a random seed
    
    // for output 'data.dat' file
    outFile.open("data//output//onemax-hc.dat",ofstream::out);

    // read all arguments to *all_args*
    vector<string> all_args;
    all_args.assign(argv+1, argv+argc);

    int bits = stoi(all_args[0]);
    int durations = stoi(all_args[1]);
    int range = stoi(all_args[2]);

    // init the bitstring, default is all zero
    // btw, it also can be set in random case
    vector<bool> onemax = initialization(bits);
    vector<bool> tmp;

    // count for iterations
    int iterations = 0;

    /* while iterations as known as SELECTION STAGE  */ 
    while ((eval(onemax) < bits) && _durations < durations){
        iterations++;
        /* btw, we also can apply some aggrasive approach here */
        /* by multi-tweak at the same time, and pick up the highest eval(onemax) one */
        tmp = tweak(onemax,range);

        int tmp_oneCount = eval(tmp);
        int onemax_oneCount = eval(onemax);
        // find some tweak is better than older, then update it
        if (tmp_oneCount > onemax_oneCount){
            onemax = tmp;
            for (int i = 0; i < bits ; i ++){
                outFile << onemax[i];
                cout << onemax[i];
            }
            cout << ", one count is : " << eval(onemax) << endl;
            outFile << ' ' << iterations << ' ' << _durations << ' ' << eval(onemax) << '\n';
        }

        // use for controlling process duration limit
        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;
        _durations = durations.count();
    }
}

// init the bitstring, default is all zero
// btw, it also can be set in random case
vector<bool> initialization(int bits){
    vector<bool> onemax;
    for (int i = 0; i < bits ; i++){
        onemax.push_back(0);
    }
    return onemax;
}

/* the most important part */ 
/* here we use the random search skill, it will tweak some portion of bitstring */
vector<bool> tweak(vector<bool> origin, int range){
    vector<bool> tmp = origin; // copy the origin bitstring, use for tweaking
    int len = tmp.size();
    int begin = rand() % len;

    // store the eval(origin) value, for detect replace bitstring or not
    int onecount_origin = eval_in_range(tmp,begin,range);

    // here we apply random skill to portion of bitstring
    for (int i = 0; i < range; i++){
        tmp[(begin+i)%len] = rand() % 2; // cycled affect portion of bitstring
    }
    int onecount_tmp = eval_in_range(tmp,begin,range); // then we got eval(tmp), so we can detect which is better


    if (onecount_tmp > onecount_origin){
        // use for output the durations for Tweak process
        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;

        onecount_origin = onecount_tmp;
        cout << "> Tweak successed, duration :" << durations.count() << endl;
        _durations =  durations.count();

        // when eval(tmp) > eval(origin) then replace the origin bitstring
        return tmp;
    }else{
        // keep the origin bitstring
        return origin;
    }
    
}

int eval_in_range(vector<bool> tmp, int begin, int range){
    int len = tmp.size();
    int onecount = 0;
    for(int i = 0; i < range; i++){
        if (tmp[(begin+i)%len] == 1){
            onecount++;
        }
    }
    return onecount;
}

int eval(vector<bool> bitset){
    int len = bitset.size();
    int oneCount = 0;
    for (int i = 0;i<len;i++){
        if (bitset[i] == 1){
            oneCount++;
        }
    }
    return oneCount;
}