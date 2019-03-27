#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SIGNCERT "/usr/share/jailbreak/signcert.p12"
#define SIGNARG "-K/usr/share/jailbreak/signcert.p12"
#define LDID "/usr/libexec/ldid"

int main(int argc, char **argv, char **envp) {
    bool arg_S=false;
    bool arg_K=false;
    int newargc = argc;
    char **newargv = argv;

    if (access(SIGNCERT, R_OK)==0) {
        for (int i=1; i<argc && (!arg_S || !arg_K); i++) {
            if (strstr(argv[i], "-S") == argv[i]) arg_S=true;
            if (strstr(argv[i], "-K") == argv[i]) arg_K=true;
        }
        if (arg_S && !arg_K) {
            newargc += 1;
            newargv = malloc((newargc+1) * sizeof(char *));
            newargv[0] = argv[0];
            newargv[1] = SIGNARG;
            for (int i=1; i<argc; i++) {
                newargv[i+1] = argv[i];
            }
            newargv[newargc] = NULL;
        }
    }
    execv(LDID, newargv);
    return -1;
}

// vim:ft=c
