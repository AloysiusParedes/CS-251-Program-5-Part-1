

pq.o: pq.c pq.h
	gcc -c pq.c
	
test: test.c pq.o
	gcc test.c pq.o -o test