#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 127


/* function prototypes */
void write_name(char *, char *);

/* write_name: copy a username from the string pointed to by line
               to that pointed to by dest
*/
void write_name(char *line, char *dest)
{
    while (*line != ':') {
        
        *dest++ = *line++;
    }

    *dest = '\0';
}

    
int main(int argc, char **argv)
{
    
    FILE *userfile;
    char userlist[100][20];
    char buffer[BUFSIZE];
    int i=0;

    if ((userfile = fopen("/etc/passwd", "r")) == NULL) {
        fprintf(stderr, "error: could not open file\n");
        exit(1);
    }

    while (fgets(buffer, BUFSIZE, userfile) != NULL) {
        
        write_name(buffer, userlist[i++]);
    }

    for ( ; i >= 0; i--) {
        printf("%s\n", userlist[i]);
    }

    return 0;
}
    
    

