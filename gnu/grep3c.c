#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 1024
#define MAX_SIZE 1024

#define INIT_MANAGER(x) st_manager x = {.num_occur=0, .occur_index = {0}}

#define COLOUR_BLUE "\x1b[34m"
#define COLOUR_RESET "\x1b[0m"

typedef struct {
    char *pattern;
    int num_occur;
    int occur_index[MAX_LEN];
} st_manager;


void print_usage(char *prog_name)
{
    fprintf(stderr, "usage: %s [file-path] [pattern] [options]", prog_name);
    fprintf(stderr, "Options: \n");
    fprintf(stderr, "\t -n  Show the number of occurences\n");
    fprintf(stderr, "\t -d  Display whole text with pattern highlighted\n");
    fprintf(stderr, "\t -i  Show indices of occurence of pattern (0-indexed)\n");
    fprintf(stderr, "\n");
}

void display_pattern(FILE *stream, char *pattern, st_manager book)
{
    int i;
    char buffer[MAX_SIZE];
    char *line;
    int ind = 0;
    int r_ind = 0;
    int patlen = strlen(pattern);
    int pc = patlen;
    int ded_len = 0;
    int dat;

    printf("Output (pattern in blue): \n");
    printf("\n\n");

    while (fgets(buffer, MAX_SIZE, stream)) {
        
        line = buffer;
        for ( ; *line; ind++) {
            
            
            if (ind == book.occur_index[r_ind]) {
                
                while (pc--) {
                    printf(COLOUR_BLUE "%c" COLOUR_RESET, *line++);
                    ind++;
                }
                ind--;
                pc = patlen;

                r_ind++;


            } 
            else {
                printf("%c", *line++);
            }


        }

        ded_len += strlen(buffer);
            
    
    }
    printf("\n\n");


}


st_manager pat_search(FILE *stream, char *pattern)
{
    INIT_MANAGER(booker);
    char buffer[MAX_SIZE];
    char *pattern_ref = pattern;
    int patlen = strlen(pattern);
    //char input_line[MAX_LEN];
    char *input_line;

    int occurs = 0;         /* number of occurences of pattern */
    int char_mlen = 0;      /* number of character matches */ 
    int line_index = 0;
    int pos_index = 0;


    while (fgets(buffer, MAX_SIZE, stream)) {
        
        input_line = buffer;

        while (*input_line) {
            /* Try to match with first char */

            while ((*input_line != *pattern) && *input_line)   {
                input_line++; 
                line_index++;
            }

            /* Assume that, at this point, the first match has been made */

            
            while (*pattern && *input_line && *input_line == *pattern) {
                char_mlen++;
                input_line++; 
                line_index++;
                pattern++;
            }

            /* Check if a full match has been found */
            if (char_mlen == patlen) {
                occurs++;

                /* making adjustments for correct indexing */
                booker.occur_index[pos_index++] = line_index - patlen;

            }

            

            pattern = pattern_ref;
            char_mlen = 0;
        }
    }
    booker.num_occur = occurs;


    return booker;
}

void list_indices(st_manager book)
{
    int i = book.num_occur;
    int a = i;

    printf("Occurences: \n");
    while (i--) {
        printf("%d ", book.occur_index[a-i-1]);
    }

    printf("\n\n");
}

int main(int argc, char **argv)
{
    st_manager holder;

    /*options */
    char c;
    int disp_f = 0;     /* shows patterns in coloured text */
    int num_f = 0;      /* displays the number of occurences */
    int ind_f = 0;      /* lists all the indices[from 0] of occurence of pattern */

    if (argc < 3) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inp_file = fopen(argv[1], "r");
    char *pattern = argv[2];

    /* parse arguments */
    while ((c = getopt(argc, argv, "dni")) != -1)
        switch(c)
        {
            case 'd':
                disp_f = 1;
                break;
            case 'n':
                num_f = 1;
                break;
            case 'i':
                ind_f = 1;
                break;
            default:
                break;

        }

    /*
    FILE *inp_file = fopen(argv[1], "r");
    char *pattern = argv[2];
    */

    holder = pat_search(inp_file, pattern);
    
    if (num_f) { printf("occurences: %d \n", holder.num_occur); }

    if (disp_f) {
        //rewind file as it has already been read
        fseek(inp_file, 0, SEEK_SET);
        display_pattern(inp_file, pattern, holder);
    }

    if (ind_f) {
        list_indices(holder);
    }

    fclose(inp_file);

    return EXIT_SUCCESS;
}
    
