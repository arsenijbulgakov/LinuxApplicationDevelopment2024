#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>


typedef int (*remove_type)(const char *filename);

int remove(const char *filename) {
    
    if (strstr(filename, "PROTECT")) {
        return 0;
    }

    int res = ((remove_type)(dlsym(RTLD_NEXT, "remove")))(filename);
    return res;
}