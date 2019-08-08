all:knap-sa knap-ga

knap-sa: main-knap-sa.o SA.o knap.o header.o
	g++ main-knap-sa.o SA.o knap.o header.o -o knap-sa

knap-ga: main-knap-ga.o GA.o knap.o header.o
	g++ main-knap-ga.o GA.o knap.o header.o -o knap-ga

main-knap-sa.o: main-knap-sa.cpp
	g++ -c main-knap-sa.cpp

main-knap-ga.o: main-knap-ga.cpp
	g++ -c main-knap-ga.cpp

SA.o: SA.cpp
	g++ -c SA.cpp

GA.o: GA.cpp
	g++ -c GA.cpp

knap.o: knap.cpp
	g++ -c knap.cpp

header.o: header.cpp
	g++ -c header.cpp

plot:
	gnuplot figure.plt

clear:
	rm *.o knap-sa knap-ga