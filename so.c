#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

int n_global;
int j_global;

void handlerSIGTERM() {
    srand(time(NULL));
    int r = rand() % (n_global + 1);
    if (r == j_global) {
        printf("Goodbye, %d dying\n", getpid());
        exit(0);
    } else {
        return;
    }
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    int J = atoi(argv[3]);


    pid_t pids[N];
    n_global = N;
    j_global = J;

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            signal(SIGTERM, handlerSIGTERM);
            while(1) {
                pause();
            }
        } else {
            pids[i] = pid;
        }
    }

    for (size_t j = 0; j < K; j++) {
        printf("Round %d\n", j + 1);
        for (int i = 0; i < N; i++) {
            kill(pids[i], SIGTERM);
            sleep(1);
        }
    }

    int status;
    for (size_t i = 0; i < N; i++) {
        pid_t process = pids[i];
        int result = waitpid(process, &status, WNOHANG);
        if (result == 0) {
            printf("Hijo con pid %d es ganador!\n", process);
            kill(process, SIGKILL);
        }
    }
    return 0;
}