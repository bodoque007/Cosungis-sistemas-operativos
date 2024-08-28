#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ping(int sig) {
    pid_t my_pid = getpid();
    printf("Ping from %d\n", my_pid);
    fflush(stdout);
    kill(getppid(), SIGUSR1);
}

void pong(int sig) {
    pid_t my_pid = getpid();
    printf("Pong from %d\n", my_pid);
    fflush(stdout);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        signal(SIGUSR1, ping);
        while (1) {
            pause();
        }
    } else {
        char user_input;
        signal(SIGUSR1, pong);

        do {
            // DISGUSTING sleep to make sure the child process sets up its signal handler. LOL
            sleep(1);

            for (int i = 0; i < 3; i++) {
                kill(pid, SIGUSR1);
                pause();
            }

            printf("Do you want another round of ping-pong? (y/n): ");
            fflush(stdout);
            user_input = getchar();
            while (getchar() != '\n'); // Clears buffer for next getchar() call.

        } while (user_input == 'y' || user_input == 'Y');

        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}
