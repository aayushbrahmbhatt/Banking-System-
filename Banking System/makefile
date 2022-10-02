CC=gcc
CFLAGS=-I.

deps = libmyfunc

o_files = obj/login_acc.o obj/project.o obj/query1.o obj/query2.o obj/bank_server.o obj/complain.o libmyfunc
out_files = project.out query1.out query2.out bank_server.out complain.out

obj/login_acc.o: login_acc.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/project.o: project.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/query1.o: query1.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/query2.o: query2.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/bank_server.o: bank_server.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/complain.o: complain.c
	$(CC) -c -o $@ $< $(CFLAGS)

libmyfunc:obj/login_acc.o
	ar rs $@ $< 
		


project.out:project.c
	$(CC) -o $@ $< $(deps) $(CFLAGS)

query1.out: query1.c
	$(CC) -o $@ $< $(CFLAGS)

query2.out: query2.c
	$(CC) -o $@ $< $(CFLAGS)
	
bank_server.out: bank_server.c
	$(CC) -o $@ $< $(CFLAGS)

complain.out: complain.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY:out
out:$(out_files)

.PHONY:obj
obj:$(o_files)

.PHONY:all
all: $(out_files) $(o_files)