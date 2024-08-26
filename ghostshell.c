#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define WRITE_END 1
#define READ_END 0

/*
Escribir el código de un programa que se comporte de la misma
manera que la ejecución del comando “ls -al | wc -l” en un
intérprete de comandos.
No está permitido utilizar la función system(), y cada uno de los
programas involucrados en la ejecución del comando deberá
ejecutarse como un subproceso
*/

int fd[2];

int main() {
    pipe(fd);

    pid_t ls_pid = fork();
    if (ls_pid == 0) {
        close(fd[READ_END]); 
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]); 
        execlp("ls", "ls", "-al", (char *) NULL);
    }

    pid_t wc_pid = fork();
    if (wc_pid == 0) {
        close(fd[WRITE_END]); 
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);
        execlp("wc", "wc", "-l", (char *) NULL);
    }

    close(fd[WRITE_END]);
    close(fd[READ_END]);

    waitpid(ls_pid, NULL, 0);
    waitpid(wc_pid, NULL, 0);

    return 0;
}