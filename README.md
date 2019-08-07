# Metaheuristics-Algorithm

##### Table of Contents  
* [There are *THREE MAIN STAGE*](#1)  
* [Flow Chart](#2)
* [Class Diagram](#3)
* [Sequence Diagram](#4)
* [Problem](#5)
    * [01-Knapsack](#6)
* [Search Algorithm](#7)
    * [Simulated Annealing](#8)
        * [How to escape from local optima](#9)

# There are *THREE MAIN STAGE* <a name="1"/>

* Transite
    ```
    tweak a candidate solution, which produces a
    *randomly slightly different* candidate solution
    ```    

* Evaluate
    ```
    Assess the Quality of a candidate solution
    ```   
    
* Determine
    ```
    If eval(S) > eval(tweak(S)):
        repeat the loop
    Else
        replace S by tweak(S)
        then repeat the loop
    ```
    


# Flow Chart <a name="2"/>
<img align="middle" width="50%" src="data\figure\flowChart.PNG">

# Class Diagram <a name="3"/>
<img align="middle" width="50%" src="data\figure\classDiagram.png">

# Sequence Diagram <a name="4"/>
<img align="middle" width="50%" src="data\figure\sequenceDiagram">

# Problem <a name="5"/>
## 01-Knapsack <a name="6"/>

# Search Algorithm <a name="7"/>
## Simulated Annealing <a name="8"/>
The key feature of Simulated Annealing is that it provides a mechanism to escape local optima by allowing hill-climbing moves in hopes of finding a global optimum.

### How to escape from local optima <a name="9"/>
here is a abstraction about acceptance probability, is the basic search mechanism in SA.

```
IF <tmp> isn't worse than <origin>, we'll still select <tmp> with a reasonable probability.
We're doing a *random walk* in the space. Then <temperature> decreases slowly, eventually to 0, at which point the algorithm is doing nothing more than plain Hill-Climbing.

    First thing, while <tmp> is much worse than <origin>, the fraction is larger,
and so the probability is close to 0. If <tmp> is very close to <origin>, the probability
is close to 1.

    Second, we have a *tunable parameter <t>*. If <t> is close to 0, the fractions is larger,
and so the probalility is cose to 0. If <t> is high, the probability is close to 1.
```