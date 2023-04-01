advCalc: main.o hash.o tokenizer.o parser.o
	gcc main.o hash.o tokenizer.o parser.o -o advCalc

main.o: main.c
	gcc -c main.c

hash.o: hash.c hash.h
	gcc -c hash.c

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

parser.o: parser.c parser.h
	gcc -c parser.c

clean:
	rm *.o advCalc