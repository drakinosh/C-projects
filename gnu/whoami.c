#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char **argv)
{
    struct passwd *pw_s;
    uid_t user_id = getuid();
    pw_s = getpwuid(user_id);

    printf("%s\n", pw_s->pw_name);

    return 0;
}
