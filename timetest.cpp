#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

vector<bool> tweak(vector<bool> origin, int range);
vector<bool> selection(vector<bool> onemax, int range);
int eval_in_range(vector<bool> tmp, int begin, int range);
int eval(vector<bool> bitset);

auto start = chrono::system_clock::now();


int main(){
    
    vector<bool> onemax;
    for (int i = 0; i < 100 ; i ++){
        onemax.push_back(0);
    }

    int range = 5;
    vector<bool> tmp;
    while (eval(onemax) < 100){

        // maybe here can have multi-tweak, and add begin to tweak
        tmp = tweak(onemax,range);

        int tmp_oneCount = eval(tmp);
        int onemax_oneCount = eval(onemax);
        if (tmp_oneCount > onemax_oneCount){
            onemax = tmp;
            for (int i = 0; i < 100 ; i ++){
                cout << onemax[i];
            }
            cout << ", one count is : " << eval(onemax) << endl;
        }
    }

    cout << '\n';
    system("pause");
}

vector<bool> tweak(vector<bool> origin, int range){


    vector<bool> tmp = origin;
    int len = tmp.size();
    srand(time(0));
    int begin = rand() % len;

    int onecount_origin = eval_in_range(tmp,begin,range);

    if (begin < len - range){
        for (int i = 0; i < range; i++){
            tmp[begin+i] = rand() % 2;
        }
        int onecount_tmp = eval_in_range(tmp,begin,range);
        if (onecount_tmp > onecount_origin){
            auto end = chrono::system_clock::now();
            chrono::duration<double> durations = end - start;

            onecount_origin = onecount_tmp;
            cout << "> Tweak successed, duration :" << durations.count() << endl;
            return tmp;
        }
        // second chance, scaled-scope tweak
        // maybe we can tweak Left & right recursively
    }else{
        return origin;
    }
    
}

int eval_in_range(vector<bool> tmp, int begin, int range){
    int onecount = 0;
    for(int i = 0; i < range; i++){
        if (tmp[begin+i] == 1){
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

vector<bool> selection(vector<bool> onemax, int range){

}