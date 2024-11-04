#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <rhash.h>

#include "config.h"

#ifdef USE_LIBREADLINE
#include <readline/readline.h>
#endif


void stringToUpper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}


void removeNewLine(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = 0;
            break;
        }
    }
}


int getFormatFlag(char *hashName) {
    int formatFlag;

    if (islower(hashName[0]) != 0) {
        formatFlag = RHPR_BASE64;
    } else {
        formatFlag = RHPR_HEX;
    }

    return formatFlag;
}


int main(int argc, char **argv) {

    char digest[64];
    char output[130];

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    char *hashName;
    char *text;

    rhash_library_init();

#ifdef USE_LIBREADLINE
    while (line = readline("> ")) {
#else
    while ((nread = getline(&line, &len, stdin)) != -1) {
#endif

        hashName = strtok(line, " ");
        if (hashName == NULL) {
			fprintf(stderr, "Empty string!\n");
			continue;
		}

        text = strtok(NULL, " ");
        if (text == NULL) {
			fprintf(stderr, "There is only one word!\n");
			continue;
		}
        removeNewLine(text);
        

        int formatFlag = getFormatFlag(hashName);
        stringToUpper(hashName);

        unsigned hashId;
        if (strcmp(hashName, "MD5") == 0) {
            hashId = RHASH_MD5;
        } else if (strcmp(hashName, "SHA1") == 0) {
            hashId = RHASH_SHA1;
        } else if (strcmp(hashName, "TTH") == 0) {
            hashId = RHASH_TTH;
        } else {
            fprintf(stderr, "unsupported hash: %s\n", hashName);
            continue;
        }


        bool isFile;
        if (text[0] == '"') {
            isFile = false;
        } else {
            isFile = true;
        }


        if (isFile) {
            int res = rhash_file(hashId, text, digest);
            if(res < 0) {
                fprintf(stderr, "LibRHash error: %s: %s\n", text, strerror(errno));
                continue;
            }
        } else {
            int res = rhash_msg(hashId, text + 1, strlen(text) - 1, digest);
            if(res < 0) {
                fprintf(stderr, "message digest calculation error\n");
                continue;
            }
        }
        rhash_print_bytes(output, digest, rhash_get_digest_size(hashId), formatFlag);


        printf("%s\n", output);
    }

    return 0;
}