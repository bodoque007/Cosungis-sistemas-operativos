#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define WRITE_END 1
#define READ_END 0

int fd_barto[2];
int fd_lisa[2];

void lisa() {
    int num = 0;
    write(fd_lisa[WRITE_END], &num, sizeof(num));
    close(fd_lisa[WRITE_END]);
    exit(0);
}

void barto() {
    int num = 5;
    write(fd_barto[WRITE_END], &num, sizeof(num));
    close(fd_barto[WRITE_END]);
    exit(0);
}

int main(){
    pipe(fd_barto);
    pipe(fd_lisa);

    pid_t barto_pid = fork();
    if (barto_pid == 0) {
        barto();
    }

    wait(NULL);
    pid_t lisa_pid = fork();
    if (lisa_pid == 0) {
        lisa();
    }
    
    wait(NULL);
    // Anunciar ganador
    int barto;
    int resultado_barto = read(fd_barto[READ_END], &barto, sizeof(barto));
    close(fd_barto[READ_END]);
    int lisa;
    int resultado_lisa = read(fd_lisa[READ_END], &lisa, sizeof(lisa));
    close(fd_lisa[READ_END]);

    printf("Winner is barto!\n");
    return 0;
}
