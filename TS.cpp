#include "header.h"

/*
 * TS algorithm
 */
TS::TS(Tabu *tabu)
{
    this->tabu = tabu;
}

int numberOfEvaluation;
int sequence = 1;
ofstream output;

void TS::run(Knap *knap_ptr)
{
    string path_to_outfile = "data/output/knap-ts/" + to_string(sequence) + ".txt";

    output.open(path_to_outfile);

    numberOfEvaluation = 0;

    this->knap_ptr = knap_ptr;
    int capacity = knap_ptr->getCapacity();
    vector<int> values = knap_ptr->getValues();
    vector<int> weights = knap_ptr->getWeihgts();
    vector<int> opt = knap_ptr->getOpt();

    solution origin = knap_ptr->getCandidate(); // initial candidate
    solution best = origin;
    solution candidate;
    solution tmp;

    while (best != opt && numberOfEvaluation < 20000)
    {
        if (tabu->size() >= tabu->getMaxsize())
        {
            tabu->dequeue();
        }

        candidate = mutate(origin);

        // find the better candidate in neighborhood from <S>
        // exclude the neighbor that in <Tabu>
        for (int i = 0; i < random_range; i++)
        {
            tmp = mutate(origin);
            if (!tabu->is_member(tmp) &&
                (fitness(tmp) > fitness(candidate) || tabu->is_member(candidate)) &&
                fitness_Weight(tmp) <= capacity)
            {
                candidate = tmp;
            }
        }

        if (!tabu->is_member(candidate) && fitness_Weight(candidate) <= capacity)
        {
            origin = candidate;
            tabu->enqueue(candidate);
        }

        determine(candidate, best);

        output << numberOfEvaluation << ' ' << fitness(best) << endl;
    }

    output.close();

    knap_ptr->setIteration(numberOfEvaluation);
    
    knap_ptr->setBest(best);

    sequence++;
}

// T
solution TS::mutate(solution origin)
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
double TS::fitness(solution candidate)
{
    double fitness = 0.0;
    for (int i = 0; i < candidate.size(); i++)
    {
        if (candidate[i])
        {
            fitness += double(knap_ptr->getValues()[i]);
        }
    }
    numberOfEvaluation++;
    return fitness;
}
// E-weight
double TS::fitness_Weight(solution candidate)
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
void TS::determine(solution candidate, solution &origin)
{

    /*
     *  need to be process with the corrent <Prob_ptr>
     */
    if (fitness(candidate) > fitness(origin) && fitness_Weight(candidate) <= knap_ptr->getCapacity())
    {
        origin = candidate;
    }
}

/* getter and setter */
void TS::setRandomRange(int random_range) { this->random_range = random_range; }
int TS::getRandomRange() { return this->random_range; }

/*
 * Tabu 
 */
Tabu::Tabu(int maxsize)
{
    this->maxsize = maxsize;
}
void Tabu::enqueue(solution tmp)
{
    tabuList.push_back(tmp);
}
void Tabu::dequeue()
{
    tabuList.erase(tabuList.begin());
}
int Tabu::is_member(solution candidate)
{
    for (int i = 0; i < tabuList.size(); i++)
    {
        if (tabuList[i] == candidate)
        {
            return 1;
        }
    }
    return 0;
}
int Tabu::size()
{
    return tabuList.size();
}

int Tabu::getMaxsize() { return maxsize; }