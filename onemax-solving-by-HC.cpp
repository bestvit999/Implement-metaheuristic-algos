#include <string>
#include <iostream>
#include <vector>
#include <fstream> // for outFile
#include <cstdlib> // for random
#include <ctime> // change random seed by time
#include <chrono> // for compute duration

using namespace std;

int maxCount = 0;

// init the bitstring from giving bit size
vector<bool> initialization(int);
// find next candidate bit string to be evaluated
void tweak(vector<bool> & bitset,int begin, int end, double duration);
// evaluate the number of one in bit string
int eval(vector<bool> bitset);
int eval_in_range(vector<bool> bitset, int begin, int end);
// show current one-max value
int currentMax(int oneCount);

int main(int argc,char * argv[]){
    
    // for output dataset
    ofstream outFile;
    outFile.open("data/dataset-hc.dat",ofstream::out);

    vector<string> all_args;
    // read all arguments to *all_args*
    all_args.assign(argv+1,argv+argc);

    // init the bitstring, default is all zero
    // btw, it also can be set in random case
    vector<bool> bitset = initialization(stoi(all_args[0]));
    // iterminal condition
    unsigned long long termial_iterations = stoi(all_args[1]);

    // count current iterations
    unsigned long long iters = 0;

    /* this stage is SELECTION */
    /* it will select the higher eval(<bitset>) as new bitset */
    // when the number of one < number of one-max that we want, then keep looking
    while((eval(bitset) < stoi(all_args[0])) && iters < termial_iterations ){
        
        
        tweak(/* CODE HERE */); // find next condidate bit string to be evaluated
        
        // print the bitstring current status
        for (int i = 0;i<bitset.size();i++){
            outFile << bitset[i];
            cout << bitset[i];
        }

        int oneCount = eval(bitset);
        cout << " one count is : " << oneCount << ", current Max is : " << currentMax(oneCount) << '\n';
        
        outFile << ' ' << oneCount << '\n';
        iters++;
    }

    outFile.close();

    cout << '\n';
    system("pause");
}

// init at random point to start searching
vector<bool> initialization(int bits){
    vector<bool> b;
    // set random seed
    srand(time(0)); 
    // default setting, we assign all zero to bitstring
    for (int i = 0;i<bits;i++){
        int x = rand() % 2;
        b.push_back(x);
    }
    return b;
}

// maybe we can have tweak *more than one bitsting* at the same time
// and we can setting a range, so we can apply tweak in a <specific range> 
// also can setting a <Time duration>, that used to terminate Tweak
void tweak(vector<bool> & bitset,int begin, int end, double duration){
    int onemaxCount = eval_in_range(bitset,begin,end);
    vector<bool> tmpBitset = bitset;

    auto start = chrono::system_clock::now();
    while(1){

        

        auto end = chrono::system_clock::now();
        chrono::duration<double> durations = end - start;
        if (durations.count() > duration){
            break;
        }
    }
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

int eval_in_range(vector<bool> bitset, int begin, int end){
    int len = bitset.size();
    int oneCount = 0;
    for (int i = 0;i<len;i++){
        if (bitset[i] == 1){
            oneCount++;
        }
    }
    return oneCount;
}

int currentMax(int oneCount){
    if (oneCount > maxCount){
        maxCount = oneCount;
    }
}