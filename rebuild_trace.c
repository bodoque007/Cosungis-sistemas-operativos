#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void julieta() {
    printf("Soy Julieta\n");
    sleep(1);
    pid_t pid = fork();
    if (pid == 0) {
        jennifer();
    } else {
        exit(0);
    }
}

void jennifer() {
    printf("Soy Jennifer\n");
    sleep(1);
    exit(0);
}

void jorge() {
    printf("Soy Jorge\n");
    sleep(1);
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        julieta();
    } else {
        printf("Soy Juan\n");
        sleep(1);
        wait(NULL);
    }
    pid = fork();
    if (pid > 0) {
        exit(0);
    } else {
        jorge();
    }
    return 0;
}