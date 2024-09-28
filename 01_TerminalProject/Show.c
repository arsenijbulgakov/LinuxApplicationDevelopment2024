#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE_LENGTH 100

#define DX 7
#define DY 3


typedef struct strings {
    char **lst;
    int size;
} stringLst;


void removeNewLine(char *str, const int size) {
    for (int i = 0; i < size && str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = 0;
            break;
        }
    }
}


bool endsWithNewline(char *str, const int size) {
    for (int i = 0; i < size && str[i]; i++) {
        if (str[i] == '\n') {
            return true;
        }
    }
    return false;
}


void readEndOfLine(FILE *file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            break;
        }
    }
}


void printLines(stringLst fileLines) {
    for (int i = 0; i < fileLines.size; i++) {
        printf("%s\n", fileLines.lst[i]);
    }
}


stringLst readFileLines(const char *fileName) {
    FILE *file;
    int numStrings = 5;
    int curNumStrings = 0;
    char **fileStrings = malloc(numStrings * sizeof(char *));

    file = fopen(fileName, "r");

    char buf[MAX_LINE_LENGTH];


    while (fgets(buf, sizeof(buf), file)) {
        if (curNumStrings >= numStrings) {
            numStrings *= 2;
            fileStrings = realloc(fileStrings, numStrings * sizeof(char *));
        }
        fileStrings[curNumStrings] = strdup(buf);
        removeNewLine(fileStrings[curNumStrings], sizeof(buf));
        curNumStrings += 1;

        if (endsWithNewline(buf, sizeof(buf))) {
            continue;
        }

        readEndOfLine(file);
    }

    fclose(file);

    stringLst fileLines;
    fileLines.lst = fileStrings;
    fileLines.size = curNumStrings;


    return fileLines;
}


int main(int argc, char **argv)
{
    const char *fileName = argv[1];
    stringLst fileLines = readFileLines(fileName);

    WINDOW *frame, *win;
    int c = 0;

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();
    printw("Окно:");
    refresh();

    frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "Рамка");
    wrefresh(frame);

    win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    int start = 0;
    int stop = LINES - 2*DY - 3;
    do {
        if (c == ' ') {
            start += 1;
            stop += 1;
        }
        werase(win);
        for (int i = start; i < fileLines.size && i < stop; i++) {
            wprintw(win, "%s\n", fileLines.lst[i]);
        }
    } while ((c = wgetch(win)) != 27);


    delwin(win);
    delwin(frame);
    endwin();
    return 0;
}