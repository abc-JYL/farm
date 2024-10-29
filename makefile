P=main
OBJS=main.o langpack.o save.o
CFLAGS=-Wall -Werror

$(P): $(OBJS)
	$(CC) $(OBJS) -o main

.PHONY: clean
clean:
	rm main *.o

