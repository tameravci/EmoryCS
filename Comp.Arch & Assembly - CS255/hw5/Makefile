
main: main.o primes.o header.h
	gcc  -o main  main.o primes.o 

%.o: %.c  header.h
	gcc -c $<

