#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1024
#define MAX_SIZE 1024

#define INIT_MANAGER(x) manager x = {.num_occur=0, .occur_index = {0}}

typedef struct {
    char *pattern;
    int num_occur;
    int occur_index[MAX_LEN];
} st_manager;

int  pat_search(FILE *stream, char *pattern)
{
    char buffer[MAX_SIZE];
    char *pattern_ref = pattern;
    int patlen = strlen(pattern);
    //char input_line[MAX_LEN];
    char *input_line;

    int occurs = 0;         /* number of occurences of pattern */
    int char_mlen = 0;      /* number of character matches */ 

    while (fgets(buffer, MAX_SIZE, stream)) {
        
        input_line = buffer;

        while (*input_line) {
            /* Try to match with first char */

            while ((*input_line != *pattern) && *input_line)   {
                input_line++;
            }

            /* Assume that, at this point, the first match has been made */

            
            while (*pattern && *input_line && *input_line == *pattern) {
                //printf("sucmatch %c \n", *pattern);
                char_mlen++;
                input_line++;
                pattern++;
            }

            /* Check if a full match has been found */
            if (char_mlen == patlen) {
                occurs++;
            }

            

            pattern = pattern_ref;
            char_mlen = 0;
        }
    }

    return occurs;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "wrong usage\n");
        return EXIT_FAILURE;
    }

    FILE *inp_file = fopen(argv[1], "r");
    char *pattern = argv[2];

    int occurs = pat_search(inp_file, pattern);
    printf("OCCURS: %d \n", occurs);

    fclose(inp_file);

    return EXIT_SUCCESS;
}






            


        
        



    
