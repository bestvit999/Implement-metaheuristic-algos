make

# knap-sa {path_to_dataset} {runs} {temperature} {alpha / cooling rate}
./knap-sa data/set6 10 10000 0.999

# knap-ga {path_to_dataset} {runs} {population size}
./knap-ga data/set6 10 4

# knap-ts {path_to_dataset} {runs} {tabu size} 
./knap-ts data/set6 10 5

## plot gs sa ts with best dataset
## replace the ${variable} with index
# sed -e 's/$minsa/~~/g' -e  's/$minga/~~/g' -e 's/$mints/~~/g' test.plt > output.plt


make plot