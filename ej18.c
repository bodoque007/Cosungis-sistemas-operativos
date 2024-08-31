#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define READ_END 0
#define WRITE_END 1


void nieto(int numero, int pipe[2]) {
    int resultado = calcular(numero);
    write(pipe[WRITE_END], &resultado, sizeof(resultado));
    kill(SIGUSR1, getppid());
    exit(0);
}

void ejecutarHijo(int i, int pipes[][2]) {
    pid_t nieto = fork();
    int numero;
    // Acá el nieto le da el resultado del calculo al hijo.
    int pipeNieto[2];
    pipe(pipeNieto);

    read(pipes[i][READ_END], &numero, sizeof(numero));
    signal(SIGUSR1, darResultadoAPadre);
    if (nieto == 0) {
        nieto(numero, pipeNieto);
    }
    wait(NULL);
    int resultado;
    read(pipeNieto[READ_END], &resultado, sizeof(resultado));
    // Ahora hay que responder que sí al pooling del padre y mandarle el result
    write(pipes[N + i][WRITE_END], 1, sizeof(1));
    write(pipes[N + i][WRITE_END], &resultado, sizeof(resultado));
}