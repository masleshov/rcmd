debug:
	gcc -D DEBUG -Wall main.c types.h reply.h util.h types.c reply.c util.c -g -o rcmd -L./lib -lhiredis
release:
	gcc -Wall main.c types.h reply.h util.h types.c reply.c util.c -o rcmd -L./lib -lhiredis
clean:
	rm -rf *.o rcmd