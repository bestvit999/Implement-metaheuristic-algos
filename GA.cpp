#include "header.h"

GA::GA(int popsize) { this->popsize = popsize; }


int numberOfEvaluation;
int sequence = 1;
ofstream output;

/* 
 * MAIN SECTION
 * 01-kanp with SA
 */
void GA::run(Knap *prob_ptr)
{
    
    string path_to_outfile = "data/output/knap-ga/" + to_string(sequence) + ".txt";
    output.open(path_to_outfile);
    numberOfEvaluation = 0;

    this->knap_ptr = prob_ptr;

    int capcity = knap_ptr->getCapacity();
    vector<int> values = knap_ptr->getValues();
    vector<int> weights = knap_ptr->getWeihgts();
    vector<int> opt = knap_ptr->getOpt();

    population pop = init(popsize); // base generation
    population cpop;                // popolation for new individuals
    solution best;                  // track best individaul
    solution bestInPop;
    vector<solution> parents;
    vector<solution> childs;

    /* MAIN SECTION */
    while (best != opt)
    {
        determine(pop,best);

        for (int i = 0; i < popsize / 2; i++)
        {
            parents = selectParent(pop); // select two parents to recombine the genes
            childs = recombination(parents);

            cpop.push_back(mutate(childs[0])); // join the childs to next generation (cpop)
            cpop.push_back(mutate(childs[1]));
        }

        pop = cpop;   // replace the formor generation
        cpop.clear(); // remember to clear the cpop

        output << numberOfEvaluation << ' ' << fitness(best) << endl;
    }

    knap_ptr->setIteration(numberOfEvaluation);

    if (best == opt){
        cout << "opt found! > ";
        showSolution(best);
        cout << endl;
    }

    output.close();

    knap_ptr->setIteration(numberOfEvaluation);

    sequence++;
}

/*
* GA operations [TED] T:transite(mutate) E:evaluate D:determine
*
* Remarks :
*      apply the implementation of different Problems, and it can be sovled by the type of <Prob_ptr>
*/

solution GA::mutate(solution origin)
{
    double p = 1.0 / double(origin.size()); // often p is `1 / # gene of chromosome`
    double randnum = 0;
    for (int i =0;i < origin.size();i++){
        randnum = double(rand()) / RAND_MAX;
        if (p >= randnum){
            origin[i] = origin[i] == 0 ? 1 : 0;
        }
    }
    return origin;
}

double GA::fitness(solution individual)
{
    double fitness = 0.0;
    for (int i = 0; i < individual.size(); i++)
    {
        if (individual[i])
        {
            fitness += double(knap_ptr->getValues()[i]);
        }
    }

    numberOfEvaluation++;
    return fitness;
}

double GA::fitness_weight(solution candidate)
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

void GA::determine(population pop, solution &origin)
{
    for (int i = 0;i<popsize;i++){
        if (fitness(pop[i]) > fitness(origin) && fitness_weight(pop[i]) <= knap_ptr->getCapacity()){
            origin = pop[i];
            cout << "cadidate : ";
            for(int j = 0;j < origin.size();j++){
                cout << origin[j];
            }
            cout << ", fitness : " << fitness(origin) << endl;
        }
    }
}

population GA::init(int popsize)
{
    population population;
    solution individual;

    for (int i = 0; i < popsize; i++)
    {
        for (int j = 0; j < knap_ptr->getCandidate().size(); j++)
        {
            individual.push_back(rand() % 2);
        }
        population.push_back(individual);
        individual.clear();
    }
    return population;
}

vector<solution> GA::selectParent(population pop)
{
    vector<solution> parents;
    // sort by value before selection
    quickSort(pop, 0, pop.size() - 1);

    // pick two parents in population by *Roulette Wheel* scheme
    vector<double> cumsum = cumulateSum(pop);

    parents.push_back(rouletteWheel(pop, cumsum));
    parents.push_back(rouletteWheel(pop, cumsum));

    return parents;
}

vector<double> GA::cumulateSum(population population)
{
    vector<double> cumulatedSum;
    double popsum = summation(population);
    for (int i = 0; i < population.size(); i++)
    {
        double cumulated = 0.0;
        for (int j = i; j < population.size(); j++)
        {
            // cumulated the *normalized fitness* from [i] to [end]
            cumulated += double(fitness(population[j])) / popsum;
        }
        cumulatedSum.push_back(cumulated);
    }
    cumulatedSum.push_back(0.0); // just for bounding
    return cumulatedSum;
}

solution GA::rouletteWheel(population pop, vector<double> cumsum)
{
    /* 
     * r = randnum between 0-1
     * IF the cumsum be picked from rouletteWheel > r
     * Then return the parent that corresponding to cumsum
     */

    double r = double(rand()) / RAND_MAX;
    solution parent;

    for (int i = 0; i < cumsum.size(); i++)
    {
        if (r == 1)
        {
            parent = pop[0];
            break;
        }
        if (r == 0)
        {
            parent = pop[pop.size() - 1];
            break;
        }
        if (r > cumsum[i])
        {
            parent = pop[i - 1];
            break;
        }
    }
    return parent;
}

int GA::partition(population arr, int front, int end)
{
    int pivot = fitness(arr[end]);
    int i = front - 1;
    for (int j = front; j < end; j++)
    {
        if (fitness(arr[j]) > pivot)
        {
            i++;
            arr[i].swap(arr[j]);
        }
    }
    i++;
    arr[i].swap(arr[end]);
    return i;
}
void GA::quickSort(population arr, int front, int end)
{
    if (front < end)
    {
        int pivot = partition(arr, front, end);
        quickSort(arr, front, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}
double GA::summation(population population)
{
    double sum = 0;
    for (int i = 0; i < population.size(); i++)
    {
        sum += fitness(population[i]);
    }
    return sum;
}

// here we apply *uniform crossover*
// Remark : also can be apply to recombine the multi-parents
vector<solution> GA::recombination(vector<solution> parents)
{
    /*
     * we have probability to exchange the genes
     * IF p > randnum
     * Then exchange the gene
     */
    
    vector<solution> childs;
    solution c1 = parents[0];
    solution c2 = parents[1];

    double p = 1.0 / double(c1.size()); // often p is set to `1 / # genes of individual`, or p <= 0.5
    double randnum = 0;

    for (int i = 0; i < c1.size(); i++)
    {
        randnum = double(rand()) / RAND_MAX;
        if (p >= randnum)
        {
            crossingover(c1, c2, i);
        }
    }

    childs.push_back(c1);
    childs.push_back(c2);

    return childs;
}

// gene exchange
void GA::crossingover(solution &chromosoem1, solution &chromosome2, int index)
{
    int tmp = chromosoem1[index];
    chromosoem1[index] = chromosome2[index];
    chromosome2[index] = tmp;
}

/*
 * getter and setter
 */
int GA::getRandomRange() { return random_range; }
void GA::setRandomRange(int _random_range) { random_range = _random_range; }