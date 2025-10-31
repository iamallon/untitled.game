CC = c99
CFLAGS = -O2 -I/opt/homebrew/Cellar/raylib/5.5/include
LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.5/lib
LDLIBS = -lraylib

all: untitled.game.a

untitled.game.a: main.o plane.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

plane.o: plane.c plane.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f untitled.game.a main.o plane.o
