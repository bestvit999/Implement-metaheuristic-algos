#include <string>
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
using namespace std;

/* attribute */
// current one-max count
int maxCount = 0;
// use for storing best bitsting
vector<bool> bestBitSet;

/* method */
// init the bitstring from giving bit size
vector<bool> initialization(int);
// find next candidate bit string to be evaluated
void tweak(vector<bool> & bitset,int end, int carryIn);
// evaluate the number of one in bit string
int evaluate(vector<bool> bitset);
// show current one-max value, and store bitsting to <bestBitSet>
int currentMax(int oneCount,vector<bool> bitset);

int main(int argc,char * argv[]){
    
    // for output dataset
    ofstream outFile;
    outFile.open("data/dataset-es.dat",ofstream::out);

    vector<string> all_args;
    // read all arguments to *all_args*
    all_args.assign(argv+1,argv+argc);

    // init the bitstring, default is all zero
    // btw, it also can be set in random case
    vector<bool> bitset = initialization(stoi(all_args[0]));
    // iterminal condition
    unsigned long long termial_iterations = stoi(all_args[1]);


    // when the number of one < number of one-max that we want
    // then keep looking 
    while(evaluate(bitset) < stoi(all_args[0])){
        tweak(bitset,bitset.size()-1,1); // find next condidate bit string to be evaluated
        
        // print the bitstring current status
        for (int i = 0;i<bitset.size();i++){
            outFile << bitset[i];
            cout << bitset[i];
        }
        int oneCount = evaluate(bitset);
        cout << " one count is : " << oneCount << ", current Max is : " << currentMax(oneCount,bitset) << '\n';
    }

    outFile.close();

    cout << '\n';
    system("pause");
}

vector<bool> initialization(int bits){
    vector<bool> b;
    // default setting, we assign all zero to bitstring
    for (int i = 0;i<bits;i++){
        b.push_back(0);
    }
    return b;
}


// recursively to setting next candidate by adding '1' to bitstring.
// use adding method below is due to either <ulong> or <ullong> both could happend overflow issue 
void tweak(vector<bool> & bitset,int end, int carryIn){
    if (end < 0) { return; }

    if (bitset[end] == 1 && carryIn == 1){
        bitset[end] = 0;
        carryIn = 1;
        tweak(bitset,end-1,carryIn);
    }else if (bitset[end] == 1 && carryIn == 0){
        return;
    }else if (bitset[end] == 0 && carryIn == 1){
        bitset[end] = 1;
        carryIn = 0;
        return;
    }else if (bitset[end] == 0 && carryIn == 0){
        return;
    }
}

int evaluate(vector<bool> bitset){
    int len = bitset.size();
    int oneCount = 0;
    for (int i = 0;i<len;i++){
        if (bitset[i] == 1){
            oneCount++;
        }
    }
    return oneCount;
}

int currentMax(int oneCount,vector<bool> bitset){
    if (oneCount > maxCount){
        maxCount = oneCount;
        copy(bitset.begin(),bitset.end(),bestBitSet);
    }
}