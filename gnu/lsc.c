/*
@desc clone of ls
@author Sanskar Chand
@date 2015-11-04

*/ 
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define DSIZE 1024
#define MAXDIRS 1024

/* The gnome terminal does not seem to be able
   to handle yellow, red and green.
   xterm and others handle it exactly according
   to ANSI rules.
*/

#define COLOUR_BLUE "\x1b[34m"
#define COLOUR_NANDEMO "\x1b[32m"
#define COLOUR_RED "\x1b[31m"
#define COLOUR_RESET "\x1b[0m"

void print_perms(struct stat);
void print_size(struct stat);
int compare_direntp(const void **, const void **);

int main(int argc, char *argv[])
{ 
    DIR *dsp;
    struct dirent *entlist[MAXDIRS] = {0};
    struct stat stat_buf;
    struct tm *tsp;

    char path[DSIZE];
    int show_perm = 0;      /* show file permissions */
    int show_size = 0;      /* atarimae darou */
    int show_last_access = 0;
    int c, j;
    int i = 0;

    while ((c = getopt(argc, argv, "spt")) != -1)
        switch(c) {
            case 'p':
                show_perm = 1;
                break;
            case 's':
                show_size = 1;
                break;
            case 't':
                show_last_access = 1;
                break;
            default:
                break;
        }
    
    /* if a directory name is provided, use it */
    if (argv[optind]) 
        strcpy(path, argv[optind]);
    else
        getcwd(path, sizeof(path));
    
    dsp = opendir(path);
    

    if (dsp) {
        while ((entlist[i++] = readdir(dsp)))
            ;

        i--;    /* number of entries */   
        printf("TOTAL ENTRIES: %d \n", i);
        qsort(entlist, i, sizeof(struct dirent *), compare_direntp);
        j = 0;
        while (j < i) { 
            stat(entlist[j]->d_name, &stat_buf);
            if (show_perm)
                print_perms(stat_buf); 
            if (show_size)
                print_size(stat_buf);
            if (show_last_access) {
                tsp = gmtime(&(stat_buf.st_atime));
                printf("%-2d:%-2d:%-2d ", tsp->tm_hour, tsp->tm_min, tsp->tm_sec);
            }

            /* print yellow text if directory */
            if (S_ISDIR(stat_buf.st_mode))
                printf(COLOUR_NANDEMO "%s\n" COLOUR_RESET, entlist[j]->d_name); 
            /* print blue text if regular and executable by owner */
            else if (S_ISREG(stat_buf.st_mode) && (stat_buf.st_mode & S_IXUSR)) 
                printf(COLOUR_BLUE "%s \n" COLOUR_RESET, entlist[j]->d_name);
            else 
                printf("%s \n", entlist[j]->d_name);

            j++;
        }
        closedir(dsp);
    }

    else
        perror("error: could not access directory\n");

    return 0;
}

/* print_perms: print the permission bits of a file */
void print_perms(struct stat statbuf)
{
    //stat(dir->d_name, &statbuf);
    
    /* prints file permissions in the form:
        (owner) (group) (other)
    */

    printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
    printf("  ");
}

void print_size(struct stat stbuf)
{
    printf("%-10d", (int) stbuf.st_size);
}

/* compare_direntp: compares two dirent pointers
    on the basis of their associated filenames */
int compare_direntp(const void **a, const void **b)
{
    const struct dirent *dp1 = *(const struct dirent **) a;
    const struct dirent *dp2 = *(const struct dirent **) b;
    
    return strcmp(dp1->d_name, dp2->d_name);
}
