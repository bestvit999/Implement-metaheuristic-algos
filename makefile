knap-ts: main-knap-ts.o TS.o knap.o header.o
	g++ main-knap-ts.o TS.o knap.o header.o -o knap-ts

knap-sa: main-knap-sa.o SA.o knap.o header.o
	g++ main-knap-sa.o SA.o knap.o header.o -o knap-sa

knap-ga: main-knap-ga.o GA.o knap.o header.o
	g++ main-knap-ga.o GA.o knap.o header.o -o knap-ga

func-pso: main-func-pso.o pso.o header.o
	g++ main-func-pso.o pso.o -o main-pso

main-knap-sa.o: main-knap-sa.cpp
	g++ -c main-knap-sa.cpp

main-knap-ga.o: main-knap-ga.cpp
	g++ -c main-knap-ga.cpp

main-func-pso.o: main-func-pso.cpp
	g++ -c main-func-pso.cpp

SA.o: SA.cpp
	g++ -c SA.cpp

GA.o: GA.cpp
	g++ -c GA.cpp

TS.o: TS.cpp
	g++ -c TS.cpp

pso.o: pso.cpp
	g++ -c pso.cpp

knap.o: knap.cpp
	g++ -c knap.cpp

header.o: header.cpp
	g++ -c header.cpp

plot:
	gnuplot figure.plt

psoplot:
	gnuplot tmp.plt

clear:
	rm *.o knap-sa knap-ga knap-ts func-pso figure.plt *.png tmp.plt out.dat

clrplot:
	rm out.dat data/figure/pso/3d/*.png data/figure/pso/2d/*.png