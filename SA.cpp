#include "header.h"

SA::SA(double temperature)
{
    this->temperature = temperature;
}

/* MAIN SECTION */
/* 01-kanp with SA */
void SA::run(Knap *prob_ptr)
{

    srand(time(0));
    double _temperature = temperature;
    this->knap_ptr = prob_ptr;

    int capcity = knap_ptr->getCapacity();
    vector<int> values = knap_ptr->getValues();
    vector<int> weights = knap_ptr->getWeihgts();
    vector<int> opt = knap_ptr->getOpt();

    solution origin = knap_ptr->getCandidate(); // initial candidate
    solution best = origin;
    solution tmp;

    int iter = 0;
    while (best != opt && _temperature > __DBL_EPSILON__)
    {
        tmp = mutate(origin, random_range); // T
        determine(tmp, origin);             // ED

        _temperature *= 0.999; // decrease t

        if (fitness(origin) > fitness(best))
        {
            best = origin;
        }
        iter++;
    }

    if (best == opt)
    {
        cout << '\n';
        cout << "opt found!" << endl;
    }

    knap_ptr->setIteration(iter);
}

/*
* SA operations [TED] T:transite(mutate) E:evaluate D:determine
*
* Remarks :
*      apply the implementation of different Problems, and it can be sovled by the type of <Prob_ptr>
*/

// T
solution SA::mutate(solution origin, int random_range)
{
    if (random_range > origin.size())
        random_range = origin.size();
    for (int i = 0; i < random_range; i++)
    {
        int index = rand() % origin.size();
        /* Bit-Flip scheme have some combinatorial problem cause that can not reach the opt */
        /* e.g. when random_range = even number, it can not reach the opt */
        // origin[index] = (origin[index] == 0) ? 1 : 0;

        /* Random assign 0-1 */
        origin[index] = rand() % 2;
    }
    return origin;
}

// E-value
double SA::fitness(solution candidate)
{
    double fitness = 0.0;
    for (int i = 0; i < candidate.size(); i++)
    {
        if (candidate[i])
        {
            fitness += double(knap_ptr->getValues()[i]);
        }
    }
    return fitness;
}
// E-weight
double SA::fitness_Weight(solution candidate)
{
    double fitness = 0.0;
    for (int i = 0; i < candidate.size(); i++)
    {
        if (candidate[i])
        {
            fitness += double(knap_ptr->getWeihgts()[i]);
        }
    }
    return fitness;
}

// D
void SA::determine(solution candidate, solution &origin)
{

    /*
     *  need to be process with the corrent <Prob_ptr>
     */
    if (fitness(candidate) > fitness(origin) && fitness_Weight(candidate) <= knap_ptr->getCapacity())
    {
        origin = candidate;
    }
    else if (fitness(candidate) < fitness(origin) && fitness_Weight(candidate) <= knap_ptr->getCapacity())
    {
        double randnum = double(rand()) / RAND_MAX;
        if (probability(candidate, origin) > randnum)
        {
            origin = candidate;
        }
    }
}

double SA::probability(solution candidate, solution origin)
{
    // here we need to find maximum due to Knapsack prob.
    // if Candidate > origin
    // then get higher Probability
    return exp((fitness(candidate) - fitness(origin)) / temperature);
}

/*
 * getter and setter
 */

int SA::getRandomRange() { return random_range; }
void SA::setRandomRange(int _random_range) { random_range = _random_range; }