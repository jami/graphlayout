#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stdout,"Usage: %s number\n",argv[0]);
        return 1;
    }

    double inputValue = atof(argv[1]);
    fprintf(stdout,"The square root of %g\n", inputValue);
    return 0;
}
