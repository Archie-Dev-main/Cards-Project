project3 : main.o cards.o
	gcc main.o cards.o -o project3

main.o : main.c cards.h
	gcc -c main.c

cards.o : cards.c cards.h
	gcc -c cards.c

clean:
    rm -rf *.o
    rm project3