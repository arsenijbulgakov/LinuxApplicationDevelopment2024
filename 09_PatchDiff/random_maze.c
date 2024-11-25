#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define N 13

void print_maze(char maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}


void init_maze(char maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i % 2 == 0) {
                maze[i][j] = '#';
            } else if (j % 2 == 0) {
                maze[i][j] = '#';
            } else {
                maze[i][j] = '.';
            }
        }
    }
}


void init_visited(bool visited[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }
}

bool check_range(int i, int j) {
    return (i >= 0) && (i < N) && (j >= 0) && (j < N);
}


void shuffle(int *array, size_t n) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}


void make_maze(int i, int j, char maze[N][N], bool visited[N][N]) {

    //int i = 1;
    //int j = 1;

    int i_next, j_next;
    int step_i, step_j;

    visited[i][j] = true;

    int steps[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
    int idxs[4] = {0, 1, 2, 3};

    shuffle(idxs, 4);
    
    step_i = steps[idxs[0]][0];
    step_j = steps[idxs[0]][1];
    i_next = i + step_i;
    j_next = j + step_j;
    if (check_range(i_next, j_next) && !visited[i_next][j_next]) {
        visited[i_next][j_next] = true;
        maze[i + step_i / 2][j + step_j / 2] = '.';
        make_maze(i_next, j_next, maze, visited);
    }

    
    step_i = steps[idxs[1]][0];
    step_j = steps[idxs[1]][1];
    i_next = i + step_i;
    j_next = j + step_j;
    if (check_range(i_next, j_next) && !visited[i_next][j_next]) {
        visited[i_next][j_next] = true;
        maze[i + step_i / 2][j + step_j / 2] = '.';
        make_maze(i_next, j_next, maze, visited);
    }

    
    step_i = steps[idxs[2]][0];
    step_j = steps[idxs[2]][1];
    i_next = i + step_i;
    j_next = j + step_j;
    if (check_range(i_next, j_next) && !visited[i_next][j_next]) {
        visited[i_next][j_next] = true;
        maze[i + step_i / 2][j + step_j / 2] = '.';
        make_maze(i_next, j_next, maze, visited);
    }

    
    step_i = steps[idxs[3]][0];
    step_j = steps[idxs[3]][1];
    i_next = i + step_i;
    j_next = j + step_j;
    if (check_range(i_next, j_next) && !visited[i_next][j_next]) {
        visited[i_next][j_next] = true;
        maze[i + step_i / 2][j + step_j / 2] = '.';
        make_maze(i_next, j_next, maze, visited);
    }
}


int main(int argc, char **argv) {

    srand(time(NULL));

    char maze[N][N];
    bool visited[N][N];

    init_maze(maze);
    init_visited(visited);

    make_maze(1, 1, maze, visited);

    print_maze(maze);

    
    return 0;
}