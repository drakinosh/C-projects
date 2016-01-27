/* @desc clone of grep
@author Sanskar  Chand @date 2015-11-06
*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 512 
/*
grepc pattern file 
*/

typedef struct data {
    int num_matches;   /* number of matches*/
    int num_lines;     /* number of lines containing matches */
} account;

void print_pattocc(char *, FILE *);

int main(int argc, char *argv[])
{  
    char *pattern;
    FILE *stream;
    
    if (!(argv[1])) 
        perror("No pattern provided\n");

    if (!(argv[2]))
        perror("No input source provided\n");
    else {
        stream = fopen(argv[2], "r");
        //exit with error
    }
    
    
    print_pattocc(argv[1], stream);
    return 0;
}

/* print pattock: prints all occurences of pattern in the stream pointed 
    to by stream */
void print_pattocc(char *pattern, FILE *stream)
{
    char buffer[MAXLEN];
    int patlen = strlen(pattern);
    int csum = 0;
    char *inp;

    printf("D: THIS ITERATION: PLEN %d \n", patlen);


    while((fgets(buffer, MAXLEN, stream)))  {
        inp = buffer;
        puts("LINK START!");
        /* iterate unitl end of line */
        while (*inp) { 
            printf("%c", *inp++);
        }
    
    }
}
