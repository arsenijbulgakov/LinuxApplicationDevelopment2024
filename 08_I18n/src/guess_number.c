#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)


int main(int argc, char **argv) {

    setlocale(LC_ALL, "");
    bindtextdomain("guess_number", LOCALE_PATH);
    textdomain("guess_number");

    int left = 0;
    int right = 100;
    int mid;
    char ans[1024];

    printf(_("Choose a number from 1 to 100\n"));

    while (right - left > 1) {
        mid = (right + left) / 2;

        printf(_("Is the number greater than %d?\n"), mid);
        scanf("%s", ans);

        if (strcmp(ans, _("yes")) == 0) {
            left = mid;
        } else if (strcmp(ans, _("no")) == 0) {
            right = mid;
        } else {
            printf(_("The answer must be yes or no. Please enter your answer again\n"));
        }
    }

    printf(_("Your numner is: %d\n"), right);

    
    return 0;
}