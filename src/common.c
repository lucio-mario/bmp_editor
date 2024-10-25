#include "common.h"

int verb = 0;

void help(void)
{
    IFDEBUG("help()");
    printf("%s - %s\n", "bitmap", "Does things with images of bitmap format.");
    printf("\nUsage: %s [-h|-v]\n", "bitmap");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-c,  --copyright, --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");

    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Lucio Mario Barbosa da Silva Filho", "luciomariobarbosa10@gmail.com");
    exit(EXIT_FAILURE);
}

void copyr(void)
{
    IFDEBUG("copyr()");
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Lucio Mario Barbosa da Silva Filho", "luciomariobarbosa10@gmail.com");
    if(verb > 3) printf("copyr(): Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}
