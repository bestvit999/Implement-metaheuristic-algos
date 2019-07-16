#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <chrono>

#define tolarant_solution_range 0.005

using namespace std;

double _duration = 0.0;

/* the polynomial function in evaluate can be replaced with which you want */
/* btw, here we can apply multi-dimension by assign multi-args */
double evaluate(double x);
double probability(double tmp, double origin, double temperature);
double tweak(double x,double neighborhood); // pick a candidate solution from neighborhood

/* Read below description to make the methodology clear */

//==================================================================================================//
//  IF <tmp> isn't worse than <origin>, we'll still select <tmp> with a reasonable probability.     //
//  We're doing a *random walk* in the space. Then <temperature> decreases slowly, eventually to 0, //
//  at which point the algorithm is doing nothing more than plain Hill-Climbing.                    //
//==================================================================================================//

//      First thing, while <tmp> is much worse than <origin>, the fraction is larger,
// and so the probability is close to 0. If <tmp> is very close to <origin>, the probability
// is close to 1.

//      Second, we have a *tunable parameter <t>*. If <t> is close to 0, the fractions is larger,
// and so the probalility is cose to 0. If <t> is high, the probability is close to 1.

int main(int argc, char * argv[]){
    auto start = chrono::system_clock::now();
    srand(time(0));

    vector<string> all_args;
    all_args.assign(argv+1,argv+argc);

    double x = 0.0; // start point at 0.0

    double temperature = stod(all_args[0]); // initially a high number
    double durations = stod(all_args[1]);
    double neighborhood = stod(all_args[2]); // search neighbor's range
    double alpha = stod(all_args[3]);
    double boundscope_start = stod(all_args[4]);
    double boundscope_end = stod(all_args[5]);
    double idealSolution = stod(all_args[6]);

    double bestX = 0.0;
    double minResult = evaluate(x); // initail solution by start point

    ofstream outFile;
    ofstream outFile_bestX_bestY;
    outFile.open("data//output//functionOpt.dat");
    outFile_bestX_bestY.open("data//output//functionOpt_bestSolution.dat");


    // terminate when bestX is {ideal solution}, {run out of time}, or {t <= 0}
    while (abs(x - idealSolution) > tolarant_solution_range && _duration < durations && temperature - __DBL_EPSILON__ > 0){
        double tmp = tweak(x,neighborhood);
        double tmpResult = evaluate(tmp);

        // searching in scope
        if (tmp >= boundscope_start && tmp <= boundscope_end){
            
            if (tmpResult < minResult) {
                minResult = tmpResult;
                x = tmp;
                bestX = tmp;
            }
            else if (tmpResult < evaluate(x)){
                x = tmp;
            }
            // If <tmp> isn't worse than <origin>, we'll still select <tmp> with a reasonable probability.
            else if (tmpResult > evaluate(x)) {
                double randomNumber = double(rand()) / RAND_MAX; // random a number between 0 and 1
                double p = probability(tmp,x,temperature);
                if (randomNumber < p){
                    x = tmp;
                }
            }

            cout << "current X is : " << x << ", current Y is : " << evaluate(x) << ", bestX is :" << bestX << ", minY is : " << minResult <<", temperature is :" << temperature << endl;
            outFile << x << ' ' << evaluate(x) << ' ' << temperature << endl;

            temperature *= alpha; // decrease <temperature> by multiply alpha

            auto end = chrono::system_clock::now();
            chrono::duration<double> durations = end - start;
            _duration = durations.count();
        }
    }
    outFile_bestX_bestY << bestX << ' ' << minResult << endl;
    outFile_bestX_bestY.close();
    outFile.close();
}

double evaluate(double x){
    return x*exp(-x)*sin(5*x)-2;
}

double probability(double tmp, double origin, double temperature){
    return exp(-(evaluate(tmp) - evaluate(origin))/temperature);
}

// pick up the candidate solution from <x> neighborhood
double tweak(double x,double neighborhood){
    double fMin = x - neighborhood;
    double randomWalk = double(rand()) / RAND_MAX;

    return fMin + randomWalk * neighborhood * 2;
}