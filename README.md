# Metaheuristics-Algoritm

## There are *FOUR MAIN STAGE*, we have some algorithm below

* Iinitialization
    ```
    assign all zero to vector 
                or
    some particular element that you want
    ```
* Modification
    ```
    *Tweak* a candidate solution, which produces a
    *randomly slightly different* candidate solution
    ```
    > Tweak as known as Modification procedure
    > btw, we can also Tweak all the elements in a vector
    

* Assessment
    ```
    Assess the Quality of a candidate solution
    ```   
    > evaluate as known as Assessment precudure
    
* Selection
    ```
    If eval(S) > eval(tweak(S)):
        repeat tweak(S)
    Else
        replace S by tweak(S)
        then repeat tweak(S)
    ```
    

# Flow Chart
<img align="middle" width="50%" src="data\figure\flowchart.png">



# Description for ONE-MAX problem


The Max One problem is a very simple problem where evolution is used to find a *specific binary string*


- Example of a random individual: <100101101101110100101010101110001>

- Target for the problem: <111111111111111111111111111111111>

The objective in this problem is to find a binary string that is identical to a specified target

> So, onemax is a *Combinatorial and Discrete problem*,
> there are tons of combinations of the answer to be found

## ONEMAX Solving By Exhaustive Search

The spirit of Exhaustive Search is very simple that consists of systematically enumerating all possible candidates for the solution and checking whether each candidate satisfies the problem's statement.

> Exhaustive Search as known as Brute-force search

### Compile and Execute
> Execute by shell command
```
$ g++ onemax-solving-by-ES.cpp
$ ./a.exe {bit size} {duration limits}
```
> e.g.
```
$ ./a.exe 100 1000
```

> It will be out put like
```
...
000000000100001101001100000110 one count is : 8, current Max is : 20
000000000100001101001100000111 one count is : 9, current Max is : 20
000000000100001101001100001000 one count is : 7, current Max is : 20
000000000100001101001100001001 one count is : 8, current Max is : 20
000000000100001101001100001010 one count is : 8, current Max is : 20
000000000100001101001100001011 one count is : 9, current Max is : 20
000000000100001101001100001100 one count is : 8, current Max is : 20
000000000100001101001100001101 one count is : 9, current Max is : 20
000000000100001101001100001110 one count is : 9, current Max is : 20
000000000100001101001100001111 one count is : 10, current Max is : 20
000000000100001101001100010000 one count is : 7, current Max is : 20
000000000100001101001100010001 one count is : 8, current Max is : 20
000000000100001101001100010010 one count is : 8, current Max is : 20
...
```

### Diagram
<img align="middle" width="100%" src="data\figure\dataset-es.png">

## ONEMAX Solving By Hill Climbing

The spirit of Hill-Climbing is that you just iteratively test new candidate solutions in the region of your current candidate, and adopt the new ones if they’re better, This enables you to climb up the hill until you reach a local optimum.

> In here, we apply Hill-Climbing with Random Range
> It means that we do Hill-Climbing for a certain random range of binary string in each iteration

### Compile and Execute
> Execute by shell command
```
$ g++ onemax-solving-by-HC.cpp
$ ./a.exe {bit size} {duration limits} {affect range}
```
> e.g.
```
$ ./a.exe 100 100 10
```

> It will be out put like
```
...
> Tweak successed, duration :0.3918
1111111111111111101111111111111111011111101111111111111111111111111111111111111111111111111111101111, one count is : 96
> Tweak successed, duration :0.396788
1111111111111111101111111111111111111111101111111111111111111111111111111111111111111111111111101111, one count is : 97
> Tweak successed, duration :0.401773
1111111111111111101111111111111111111111111111111111111111111111111111111111111111111111111111101111, one count is : 98
> Tweak successed, duration :0.407777
1111111111111111101111111111111111111111111111111111111111111111111111111111111111111111111111111111, one count is : 99
> Tweak successed, duration :0.421739
1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111, one count is : 100
```

### Diagram
<img align="middle" width="100%" src="data\figure\dataset-hc.png">


## 01-Knapsack Solving By Hill Climbing

The spirit of Hill Climbing is that you just iteratively test new candidate solutions in the region of your current candidate, and adopt the new ones if they’re better, This enables you to climb up the hill until you reach a local optimum.

> In here, we apply Hill-Climbing with Random Range
> It means that we do Hill-Climbing for a certain random range of binary string in each iteration

### Compile and Execute
> Execute by shell command
```
$ g++ knapsack-solving-by-HC.cpp
$ ./a.exe {datasetFolder} {duration limits} {random range}
```
> e.g.
```
$ ./a.exe dataset1 10 5
```

> It will be out put like
```
...
> Tweak successed, duration :0.086074
110101101110000110010110, value is : 13473482, weight is : 6366619, cp is : 2.11627
> Tweak successed, duration :0.104027
110101100110010110010111, value is : 13482886, weight is : 6383545, cp is : 2.11213
> Tweak successed, duration :0.40861
110100100110110100010101, value is : 13496672, weight is : 6402111, cp is : 2.10816
> Tweak successed, duration :0.416589
110100100110100101010111, value is : 13496748, weight is : 6402623, cp is : 2.108
> Tweak successed, duration :0.424566
110110100110100100000111, value is : 13521334, weight is : 6392842, cp is : 2.11507
> Tweak successed, duration :0.43853
110111000110100100000111, value is : 13549094, weight is : 6402560, cp is : 2.1162
```

### Diagram
<img align="middle" width="100%" src="data\figure\knapsack-hc.png">

# FunctionOpt Solving By Simulated Annealing

The key feature of *Simulated Annealing* is that it provides a mechanism to escape local optima by allowing hill-climbing moves in hopes of finding a global optimum.

> i.e., moves which worsen the objective value in a reasonable probability.

## Objective function in used

here we use the *f(x) = x * exp(-x) * sin(5*x) -2 as an example, Refer to the figure below.
<img align="middle" width="100%" src="data\figure\SAsampleFunction.png">

> and so, we'll got the global optimum point <X is near 0.940718, Y is near -2.36719>, by appling SA

## How to escape from *local optima*

here is a abstraction about *acceptance probability*, is the basic search mechanism in *SA*.
```
IF <tmp> isn't worse than <origin>, we'll still select <tmp> with a reasonable probability.
We're doing a *random walk* in the space. Then <temperature> decreases slowly, eventually to 0, at which point the algorithm is doing nothing more than plain Hill-Climbing.

    First thing, while <tmp> is much worse than <origin>, the fraction is larger,
and so the probability is close to 0. If <tmp> is very close to <origin>, the probability
is close to 1.

    Second, we have a *tunable parameter <t>*. If <t> is close to 0, the fractions is larger,
and so the probalility is cose to 0. If <t> is high, the probability is close to 1.
```

### Compile and Execute
> Execute by shell command
```
$ g++ functionOpt-solving-by-SA.cpp
$ ./a.exe {termperature} {duration limits} {neighborhood range} {tuneable alpha (cooling rate)} {boundedscope_start} {boundedscope_end} {ideal solution}
```
> e.g.
```
$ ./a.exe 1000 100 0.5 0.99 0 3 0.946745
```

> It will be out put like
```
...
current X is : 0.501007, current Y is : -1.81955, bestX is :0.940321, minY is : -2.36718, temperature is :145.197
current X is : 0.722159, current Y is : -2.1586, bestX is :0.940321, minY is : -2.36718, temperature is :143.745
current X is : 0.422117, current Y is : -1.76259, bestX is :0.940321, minY is : -2.36718, temperature is :142.307
current X is : 0.804559, current Y is : -2.27764, bestX is :0.940321, minY is : -2.36718, temperature is :140.884
current X is : 1.12041, current Y is : -2.23009, bestX is :0.940321, minY is : -2.36718, temperature is :139.476
current X is : 1.16904, current Y is : -2.15403, bestX is :0.940321, minY is : -2.36718, temperature is :138.081
current X is : 1.19588, current Y is : -2.10819, bestX is :0.940321, minY is : -2.36718, temperature is :136.7
current X is : 0.947417, current Y is : -2.36724, bestX is :0.947417, minY is : -2.36724, temperature is :135.333
```

### Diagram
> *f(x) = x * exp(-x) * sin(5*x) -2
<img align="middle" width="100%" src="data\figure\functionOpt-SA.png">

# 01-Knapsack Solving By Simulated Annealing

The key feature of *Simulated Annealing* is that it provides a mechanism to escape local optima by allowing hill-climbing moves in hopes of finding a global optimum.

> i.e., moves which worsen the objective value in a reasonable probability.

## Objective function in used

f(x) = calculate the seleted item total value

### Compile and Execute
> Execute by shell command
```
$ g++ knapsack-solving-by-SA.cpp
$ ./a.exe {datasetFolder} {temperature} {duration limits} {random range} {tuneable alpha (cooling rate)}
```
> e.g.
```
$ ./a.exe dataset1 20000 20 5 0.999
```

> It will be out put like
```
...
001100010011111000001011, best value : 12654292, iterations : 9, durations : 0.023168, temperature :19820.7
100011001001101110101100, best value : 12849751, iterations : 93, durations : 0.025184, temperature :18223
010001101100110110001111, best value : 13056617, iterations : 106, durations : 0.035879, temperature :17987.5
010101001100100110001111, best value : 13191085, iterations : 109, durations : 0.039873, temperature :17933.6
010110001110100000100100, best value : 13228738, iterations : 1730, durations : 0.047873, temperature :3542.62
110111110110000110000001, best value : 13294248, iterations : 4597, durations : 0.06772, temperature :201.177
110111000110000110011011, best value : 13361602, iterations : 8808, durations : 0.090374, temperature :2.97749
110100101110100100010100, best value : 13487268, iterations : 47492, durations : 0.236987, temperature :0.000130569
110101101110100100000100, best value : 13518963, iterations : 149690, durations : 0.618437, temperature :5.37339e-009
110111000110100100000111, best value : 13549094, iterations : 1389810, durations : 5.1407, temperature :7.08699e-014
```

### Diagram
> full view
<img align="middle" width="100%" src="data\figure\knapsack-Compare1.png">
> zoom in view
<img align="middle" width="100%" src="data\figure\knapsack-Compare2.png">
