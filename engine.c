#define _GNU_SOURCE

#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];

// ---------------- CONTAINER FUNCTION ----------------
int container_main(void *arg) {
    char **args = (char **)arg;
    char *rootfs = args[0];
    char *program = args[1];

    printf("Inside container!\n");

    // change root
    if (chroot(rootfs) != 0) {
        perror("chroot failed");
        exit(1);
    }

    chdir("/");

    // DEBUG print
    if (program != NULL) {
        printf("Trying to run: %s\n", program);

        execl(program, program, NULL);

        // if fails
        perror("exec failed");
    }

    // fallback 1 → try memory_hog
    printf("Trying fallback: /memory_hog\n");
    execl("/memory_hog", "memory_hog", NULL);

    // fallback 2 → try shell
    printf("Trying fallback: /bin/sh\n");
    execl("/bin/sh", "sh", NULL);

    perror("ALL exec failed");

    return 1;
}

// ---------------- MAIN ----------------
int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage:\n");
        printf("%s start <name> <rootfs> [program]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {

        char *name = argv[2];
        char *rootfs = argv[3];
        char *program = NULL;

        if (argc > 4) {
            program = argv[4];
        }

        printf("Starting container: %s\n", name);

        char *args[] = {rootfs, program};

        pid_t pid = clone(
            container_main,
            stack + STACK_SIZE,
            SIGCHLD,
            args
        );

        if (pid < 0) {
            perror("clone failed");
            return 1;
        }

        printf("Container %s started in background (PID: %d)\n", name, pid);

        return 0;
    }

    return 0;
}
