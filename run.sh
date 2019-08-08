make

# knap-sa {path_to_dataset} {runs} {temperature} {alpha / cooling rate}
./knap-sa data/set3 10 10000 0.999

# knap-ga {path_to_dataset} {runs} {population size}
./knap-ga data/set3 10 4

# knap-ts {path_to_dataset} {runs} {tabu size} 
./knap-ts data/set3 10 5


make plot