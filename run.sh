make

# knap-sa {path_to_dataset} {runs} {temperature} {alpha / cooling rate}
./knap-sa data/set3 10 10000 0.999

# knap-ga {path_to_dataset} {runs} {population size}
./knap-ga data/set3 10 4

# 因HC與TS為舊版本 還沒整合進入新版程式架構中
# 所以HC與TS僅附上gnuplot的結果 > gnuplot/hc-sa-ts-knap.png

make plot