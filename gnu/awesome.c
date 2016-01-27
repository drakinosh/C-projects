#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *sentence1 = "I feel awesome today!";

    fprintf(stdout, "%s\n", sentence1);

    return EXIT_SUCCESS;

}
