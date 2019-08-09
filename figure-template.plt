set xtics rotate by -45
set xlabel "number of evaluation"
set ylabel "objective value"
set term png
set output "gnuplot/result.png"
set key outside

sa = "data/output/knap-sa/$minsa.txt"
ga = "data/output/knap-ga/$minga.txt"
ts = "data/output/knap-ts/$mints.txt"

plot sa with linespoints, ga with linespoints, ts with linespoints