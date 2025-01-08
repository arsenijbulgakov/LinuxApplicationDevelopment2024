/** @mainpage
 * # Guess number program
 *
 * The user must think of a number from 1 to 100.
 * Then questions will be asked in the form: "Is your number greater than X?". You need to answer "yes" or "no". After several questions, the guessed number will be revealed

 * There are 2 operating modes:
 * 1. Arabic numerals
 * 2. Roman numerals
 *
 * Usage: ./guess_number [OPTION]
 * 
 * Options:
 * 
 *  --help: Print help message
 * 
 *  -r:     Use roman digit instead of arabic
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define INT2ROMAN_PATH "int2roman.csv"
#define MAX_ROMAN_LEN 10


typedef struct {
    int arabic;
    char roman[MAX_ROMAN_LEN];
} Int2Roman;


/** Read csv file with table pairs <arabic_number, roman_number> and fill array of these pairs
*
* @param filename name of file
* @param pairs array with pairs <arabic_number, roman_number>
*/
void readInt2RomanFile(const char* filename, Int2Roman* pairs) {
    FILE* file = fopen(filename, "r");

    char line[MAX_ROMAN_LEN];
    
    while (fgets(line, sizeof(line), file)) {
        int arabic;
        char roman[MAX_ROMAN_LEN];
        
        if (sscanf(line, "%d,%s", &arabic, roman) == 2) {
            pairs[arabic-1].arabic = arabic;
            strcpy(pairs[arabic-1].roman, roman);
        }
    }

    fclose(file);
}


/** Convert arabic number to roman number
*
* @param number number from 1 to 100
* @param pairs array with pairs <arabic_number, roman_number>
* @return string with roman number
*/
const char* arabic2Roman(int number, const Int2Roman* pairs) {
    return pairs[number-1].roman;
}


/** Convert roman number to arabic number
*
* @param roman string with roman number from 1 to 100
* @param pairs array with pairs <arabic_number, roman_number>
* @return arabic number
*/
int roman2Arabic(const char* roman, const Int2Roman* pairs) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(pairs[i].roman, roman) == 0) {
            return pairs[i].arabic;
        }
    }
}


/** Print help string
*
* @param argv array with arg variables
*/
void printHelp(char **argv) {
    printf(_("Usage: %s [OPTION]\n"), argv[0]);
    printf(_("Options:\n"));
    printf(_("    --help: Print help message\n"));
    printf(_("    -r:     Use roman digit instead of arabic\n"));
}