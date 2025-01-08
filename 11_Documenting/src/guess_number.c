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


/** @page guess_number
* Guess number program
* @section SYNOPSIS
* `guess_number` [\a OPTION]
* @section DESCRIPTION
* The user must think of a number from 1 to 100.
*
* Then questions will be asked in the form: "Is your number greater than X?".
*
* You need to answer "yes" or "no". 
*
* After several questions, the guessed number will be revealed
*
* @section OPTIONS
* --help: Print help message
*
* -r: Use roman digit instead of arabic
*/
int main(int argc, char **argv) {

    setlocale(LC_ALL, "");
    bindtextdomain("guess_number", LOCALE_PATH);
    textdomain("guess_number");

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printHelp(argv);
        return 0;
    }

    bool useRoman = false;
    Int2Roman pairs[100];
    if (argc == 2 && strcmp(argv[1], "-r") == 0) {
        useRoman = true;
    }

    readInt2RomanFile(INT2ROMAN_PATH, pairs);

    int left = 0;
    int right = 100;
    int mid;
    char ans[1024];

    if (useRoman) {
        printf(_("Choose a number from %s to %s\n"), arabic2Roman(1, pairs), arabic2Roman(100, pairs));
    } else {
        printf(_("Choose a number from 1 to 100\n"));
    }

    while (right - left > 1) {
        mid = (right + left) / 2;

        if (useRoman) {
            printf(_("Is the number greater than %s?\n"), arabic2Roman(mid, pairs));
        } else {
            printf(_("Is the number greater than %d?\n"), mid);
        }
        scanf("%s", ans);

        if (strcmp(ans, _("yes")) == 0) {
            left = mid;
        } else if (strcmp(ans, _("no")) == 0) {
            right = mid;
        } else {
            printf(_("The answer must be yes or no. Please enter your answer again\n"));
        }
    }

    if (useRoman) {
        printf(_("Your numner is: %s\n"), arabic2Roman(right, pairs));
    } else {
        printf(_("Your numner is: %d\n"), right);
    }

    
    return 0;
}
