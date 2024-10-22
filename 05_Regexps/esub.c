#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXGR 10
#define ERROR_BUF_SIZE 256


void processRegexError(int err, regex_t *regex) {
    char error_message[ERROR_BUF_SIZE];
    regerror(err, regex, error_message, sizeof(error_message));
    fprintf(stderr, "Regex error: %s\n", error_message);
    exit(1);
}



void printSubstring(const char *string, int start, int stop) {
    for (int i = start; i < stop; i++) {
        printf("%c", string[i]);
    }
}


void checkSubstitution(const char *substitution, regmatch_t bags[MAXGR]) {

    size_t len = strlen(substitution);
    for (int i = 0; i < len; i++) {

        if (substitution[i] != '\\') {
            continue;
        }

        if (substitution[i+1] >= '0' && substitution[i+1] < '9') {
            int groupNum = substitution[i+1] - '0';
            if (bags[groupNum].rm_so < 0) {
                fprintf(stderr, "There is no %d group\n", groupNum);
                exit(1);
            }
        }
    }
}


void replaceSubstitution(const char *string, const char *substitution, regmatch_t bags[MAXGR]) {
    
    size_t len = strlen(substitution);
    for (int i = 0; i < len; i++) {
        if (substitution[i] != '\\') {
            printf("%c", substitution[i]);
            continue;
        }

        if (substitution[i+1] >= '0' && substitution[i+1] < '9') {
            int groupNum = substitution[i+1] - '0';
            printSubstring(string, bags[groupNum].rm_so, bags[groupNum].rm_eo);
            i++;
        } else if (substitution[i+1] == '\\') {
            printf("%c", substitution[i+1]);
            i++;
        }
    }

}



int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "There must be exactly 3 arguments!\n");
        fprintf(stderr, "Usage: ./esub <regexp> <substitution> <string>\n");
        exit(1);
    }


    regex_t regex;
    regmatch_t bags[MAXGR];


    const char *regexp = argv[1];
    const char *substitution = argv[2];
    const char *string = argv[3];

    int regCompRes = regcomp(&regex, regexp, REG_EXTENDED);
    if (regCompRes != 0) {
        processRegexError(regCompRes, &regex);
    }

    int regRes = regexec(&regex, string, MAXGR, bags, REG_EXTENDED);

    if (regRes == 0) {
        checkSubstitution(substitution, bags);

        printSubstring(string, 0, bags[0].rm_so);
        replaceSubstitution(string, substitution, bags);
        printSubstring(string, bags[0].rm_eo, strlen(string));

        printf("\n");

    } else if (regRes == REG_NOMATCH) {
        printf("%s\n", string);
    } else {
        processRegexError(regRes, &regex);
    }

    regfree(&regex);
    return 0;
}