CC = c99
CFLAGS = -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib 

all: untitled.game.a

untitled.game.a: main.o camera.o
	$(CC) $(CFLAGS) -o $@ $^

camera.o: camera.c camera.h
	$(CC) -I/opt/homebrew/Cellar/raylib/5.5/include -o $@ -c $<

main.o: main.c
	$(CC) -I/opt/homebrew/Cellar/raylib/5.5/include -o $@ -c $^

clean:
	rm -f untitled.game.a camera.o main.o
