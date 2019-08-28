#include "header.h"

#include <thread>
#include <chrono>

void setGnuplot(int sequence);

int main()
{
    srand(time(NULL));

    int numParticle = 30;
    int dimension = 2;
    Function *f = new Function();
    PSO p = PSO(f, numParticle, dimension);

    // until gb is ideal solution
    system("make clrplot");
    int iteration = 0;
    while (!p.isOpt())
    {
        /* A. update Particle */
        /*   1. create new velocity Vt+1 */
        /*   2. move to new position */
        /*   3. update PB and GB */
        p.udpateParticle();

        setGnuplot(iteration);

        p.plot();

        this_thread::sleep_for(std::chrono::milliseconds(50));

        iteration++;
    }
}

void setGnuplot(int sequence){

    // for gnuplot the <index of output data>
    string command1 = "sed -e 's/$sequence/";
    string command2 = "/g' pso-ackley.plt > tmp.plt";
    string command = command1 + to_string(sequence) + command2;
    char const *ptr = command.c_str();
    system(ptr);

}