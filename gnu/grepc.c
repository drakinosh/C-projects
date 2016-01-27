/* @desc clone of grep
@author Sanskar  Chand @date 2015-11-06
*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 512 /*
grepc pattern file 
*/

typedef struct data {
    int num_matches;   /* number of matches*/
    int num_lines;     /* number of lines containing matches */ } account; 
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
    int line_num = 0;

    while((fgets(buffer, MAXLEN, stream)))  {
        inp = buffer;
        line_num++;
       
            /* iterate unitl end of line */           
            /* skip all unrelated characters */
        
        //printf("TS :-> %s, PAT:: %s \n", inp, pattern);
        while (*inp) {
            //printf("Start of subloop while(*inp)\n");
            while ((*inp != *pattern) && *inp) { /* skip non-matching chars */
                inp++;                           /* but not the whole line */                                                           
            }

            if (*inp == *pattern) {     /* check if a full pattern match is found */
                //printf("MATCHVAL %c, PSTRING %s\n", *inp, pattern); 
                while (*inp++ == *pattern++) {
                    csum++;
                    //printf("CSUMCUR %d \n", csum);
                }

                if (csum == patlen) {
                    printf("MATCH FOUND!\n");
                    printf("line %d: %s \n", line_num, buffer);
                } 
                --pattern;

                while (csum) {      /* back up the pattern pointer */
                
                    --pattern;
                    --csum;
                    //printf("BACKLOG VAL %s, csum %d\n", pattern, csum);
                }


            }
        }
            
    }
    
}
