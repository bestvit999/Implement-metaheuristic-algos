#include <vector>

using std::vector;

class SearchAlgo{

    protected:
        typedef vector<int> &solution;
        solution candidate;
    
    public:
        solution initialzation(int);
        solution mutate(solution,int);
        double evaluate(solution);
        solution determine(solution,solution);
        void showCand(solution);
};

class SimulatedAnnealing:SearchAlgo{
    private:
        int candidateSize;
    public:
        SimulatedAnnealing(int cand_size){
            candidateSize = cand_size;
        }

        solution initialzation(){
            for(int i = 0;i < candidateSize;i++){
                candidate.push_back(rand() % 2);
            }
        }

        solution mutate(solution cand, int range){
            for(int i = 0;i < range;i++){
                int index = rand() % cand.size();
                cand[index] = rand() % 2;
            }
            return cand;
        }

        void showCand(solution cand){
            for(int i = 0;i < cand.size();i++){
                cout << cand[i];
            }
            cout << '\n';
        }
};