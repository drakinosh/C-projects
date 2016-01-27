#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 512

int main(int argc, char **argv)
{
    char c;
    FILE *fp;
    int num_lines = 0;
    char linebuf[MAX_LINE_SIZE];

    while ((c = getopt(argc, argv, "n:")) != -1) {
        
        switch(c) {
            
            case 'n':
                num_lines = atoi(optarg);
                break;
            default:
                fprintf(stderr, "usage: head -n [fname]\n");
        }
    }
    

    /* now, open the given file */
    if ((fp = fopen(argv[argc-1], "r")) == NULL) {
        fprintf(stderr, "error: could not open file\n");
        exit(1);
    }

    if (num_lines != 0) {
        
        while (fgets(linebuf, MAX_LINE_SIZE, fp) != NULL) {
            
            if (num_lines-- > 0) {
                printf("%s", linebuf);
            }
        }
    }

    return 0;
}
