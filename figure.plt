set xlabel "number of evaluation"
set ylabel "objective value"
set term png
set output "gnuplot/result.png"

sa = "data/output/knap-sa/1.txt"
ga = "data/output/knap-ga/1.txt"

plot sa with linespoints, ga with linespoints