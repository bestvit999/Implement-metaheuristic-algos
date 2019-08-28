#include "header.h"


//=============================//
//          ALGO_PSO          //
//===========================//
PSO::PSO(Function *f,int numParticle,int dimension){
    this->f_ptr = f;
    init(numParticle, dimension);
}

void PSO::init(int numParticle,int dimension){
    for (int i = 0;i < numParticle;i++){
        particle x;
        velocity v;
        for (int j = 0;j < dimension;j++){
            double rx = -40 + (double(rand()) / RAND_MAX) * 80;
            double rv = -40 + (double(rand()) / RAND_MAX) * 80;
            x.push_back(rx);
            v.push_back(rv);
        }
        xlist.push_back(x);
        vlist.push_back(v);

        pblist.push_back(x);
    }
    initGB();
}

double PSO::evaluate(particle x){
    return f_ptr->evaluate(x);
}

void PSO::udpateParticle(){
    // B-1. create v_new for all particles
    // B-2. x_old move to new postion x_new > x_old += v_new
    // B-3. update PB and GB

    velocity v_new;
    v_new.resize(xlist[0].size());

    // v_new = w * v_old + r1 * rho1 * (pb - x_old) + r2 * rho2 * (gb - x_old)
    double w = 0.5;
    double rho1 = 0.5;
    double rho2 = 0.5;

    for(int i = 0;i < vlist.size();i++){
        double r1 = double(rand()) / RAND_MAX;
        double r2 = double(rand()) / RAND_MAX;

        for(int j = 0;j < vlist[i].size();j++){
            // B-1.
            double vi_new = w * vlist[i][j] + r1 * rho1 * (pblist[i][j] - xlist[i][j]) + r2 * rho2 * (gb[j] - xlist[i][j]);
            vlist[i][j] = vi_new;

            // B-2.
            xlist[i][j] += vi_new;
        }

        // B-3.
        if (evaluate(xlist[i]) < evaluate(pblist[i])){
            pblist[i] = xlist[i];
        }
    
        if (evaluate(xlist[i]) < evaluate(gb)){
            gb = xlist[i];
        }
    }
}
void PSO::initGB(){
    if (gb.size() == 0){
        gb = xlist[0];   
    }
    double min = evaluate(gb);
    int index;
    bool isBetter = 0;

    for(int i = 0;i < xlist.size();i++){
        if( evaluate(xlist[i]) < min){
            min = evaluate(xlist[i]);
            index = i;
            isBetter = 1;
        }
    }

    if(isBetter){
        gb = xlist[index];
    }
}

bool PSO::isOpt(){
    if(evaluate(gb) < 0.0001){
        return 1;
    }else{
        return 0;
    }
}

void PSO::showParticle(){
    for(int i = 0;i < xlist.size();i++){
        for(int j = 0;j < xlist[i].size();j++){
            cout << xlist[i][j] << ' ';
        }

        cout << " is " << evaluate(xlist[i]) << endl;
    }
}

void PSO::showGB(){
    cout << "> gb : ";
    for(int i = 0;i < gb.size();i++){
        cout << gb[i] << ' ';
    }
    cout << " is " << evaluate(gb) << endl;
}

void PSO::plot(){
    outFile();
    
    system("make psoplot");
}

void PSO::outFile(){
    ofstream output("out.dat");

    for(int i = 0;i < xlist.size();i++){
        for(int j = 0;j < xlist[i].size();j++){
            output << xlist[i][j] << ' ';
        }
        output << evaluate(xlist[i]) << endl;
    }

    output.close();
}

//=============================//
//      PROB_FUNC_ACKLEY      //
//===========================//
double Function::evaluate(particle x){
    double a = 20;
    double b = 0.2;
    double c = 2 * 3.141;

    int d = x.size(); // dimension of x

    double term1;
    double term2;
    for (int i = 0;i < d;i++){
        term1 += pow(x[i],2);
        term2 += cos(c * x[i]);
    }

    term1 = -a * exp(-b * sqrt(term1 / double(d)));
    term2 = -exp(term2/double(d));
    
    return term1 + term2 + a + exp(1); 
}