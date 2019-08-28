set isosamples 100
set hidden3d
set ticslevel 0
set view 79,28
a = 20
b = 0.2
c = 2 * 3.141

set xrange[-40:40]
set yrange[-40:40]

f(x,y) = -a * exp(-b * sqrt((x**2+y**2)/2)) -exp((cos(c*x)+cos(c*y))/2) + a + exp(1)

set term png
set output "data/figure/pso/3d/result$sequence.png"
set title "iteration : $sequence"
splot f(x,y), 'out.dat' w points pt 6 ps 2

set term png
set output "data/figure/pso/2d/result$sequence.png"
set title "iteration : $sequence"
plot 'out.dat' u 1:2 w points pt 6 ps 2


set term png
set output "result-3d.png"
set title "iteration : $sequence"
splot f(x,y), 'out.dat' w points pt 6 ps 2

set term png
set output "result-2d.png"
set title "iteration : $sequence"
plot 'out.dat' u 1:2 w points pt 6 ps 2
