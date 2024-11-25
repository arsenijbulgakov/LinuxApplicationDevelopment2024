all: random_maze random_maze_1 random_maze_2 random_maze_3

random_maze: random_maze.c
	cc random_maze.c -o random_maze

random_maze_1: random_maze.c change1.patch
	cp random_maze.c random_maze_1.c
	patch random_maze_1.c < change1.patch
	cc random_maze_1.c -o random_maze_1

random_maze_2: random_maze.c change2.patch
	cp random_maze.c random_maze_2.c
	patch random_maze_2.c < change2.patch
	cc random_maze_2.c -o random_maze_2

random_maze_3: random_maze.c change3.patch
	cp random_maze.c random_maze_3.c
	patch random_maze_3.c < change3.patch
	cc random_maze_3.c -o random_maze_3

run: all
	./random_maze
	./random_maze_1 4
	./random_maze_2 '.@' 4
	./random_maze_3 1 ' @' 4

clean:
	rm -rf random_maze random_maze_1 random_maze_2 random_maze_3 random_maze_1.c random_maze_2.c random_maze_3.c