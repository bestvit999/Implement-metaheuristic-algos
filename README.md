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
<img align="middle" width="50%" src="https://imgur.com/cQavc28.png">



# Description for ONE-MAX problem

The Max One problem is a very simple problem where evolution is used to find a *specific binary string*


- Example of a random individual: <100101101101110100101010101110001>

- Target for the problem: <111111111111111111111111111111111>

The objective in this problem is to find a binary string that is identical to a specified target

> So, onemax is a *Combinatorial and Discrete problem*,
> there are tons of combinations of the answer to be found

## ONEMAX Solving By Exhaustive Search

The spirit of Exhaustive search is very simple that consists of systematically enumerating all possible candidates for the solution and checking whether each candidate satisfies the problem's statement.

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
<img align="middle" width="50%" src="https://imgur.com/a/jcYSzA4.png">

## ONEMAX Solving By Hill Climbing

The spirit of Exhaustive search is that you just iteratively test new candidate solutions in the region of your current candidate, and adopt the new ones if they’re better, This enables you to climb up the hill until you reach a local optimum.

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
> Tweak successed, duration:80.6897
1111101111011110111110111110010011111110101011011110011110111011011011111110111101110011111001111111, one count is : 76
> Tweak successed, duration :96.6895
1111101111011110111110111110010011111110101011011110011110111011011011111110111110111011111001111111, one count is : 77
> Tweak successed, duration :99.6899
1111101111011110111110111110010011111110101011011110011110111011011011111110111110111011110111111111, one count is : 78
> Tweak successed, duration :110.689
1111101111011110111110111110111011111110101011011110011110111011011011111110111110111011110111111111, one count is : 80
> Tweak successed, duration :114.69
1111101111011110111110111110111011111110111011011110011110111011011011111110111110111011110111111111, one count is : 81
> Tweak successed, duration :127.69
1111101111011110111110111110111011111110111011011110011110111011011011111110111111101111110111111111, one count is : 82
...
```

### Diagram
<img align="middle" width="50%" src="https://imgur.com/dEVRZZQ.png">