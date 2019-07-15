# Metaheuristics-Algorithm

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
$ ./a.exe {bit size} {durations limits}
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
$ ./a.exe {bit size} {durations limits} {affect range}
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