#include "guess_number.h"


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
        printf(_("Your number is: %s\n"), arabic2Roman(right, pairs));
    } else {
        printf(_("Your number is: %d\n"), right);
    }

    
    return 0;
}
