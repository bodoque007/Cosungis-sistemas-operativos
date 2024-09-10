#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define READ_END 0
#define WRITE_END 1

typedef struct {
    int value;
    int game_over;
} Message;

int generate_random_number(){
    return (rand() % 50);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    int status, n, start, mensajeInicial, random;
    n = atoi(argv[1]);
    mensajeInicial = atoi(argv[2]);
    start = atoi(argv[3]);

    if (argc != 4){ 
        printf("Uso: anillo <n> <c> <s> \n"); 
        exit(0);
    }
    
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, mensajeInicial, start);
    
    int fd[n][2];
    for (int i = 0; i < n; i++) {
        pipe(fd[i]);
    }

    int fdPadreHijo[2], fdHijoPadre[2];
    pipe(fdPadreHijo);
    pipe(fdHijoPadre);

    pid_t *children = malloc(sizeof(pid_t) * n);

    for (int i = 0; i < n; i++) {
        children[i] = fork();
        if (children[i] == 0) { 
            if (i == start) {
                close(fdPadreHijo[WRITE_END]);
                close(fdHijoPadre[READ_END]);
                
                for (int j = 0; j < n; j++) {
                    if (j != i) close(fd[j][READ_END]);
                    if (j != (i + 1) % n) close(fd[j][WRITE_END]);
                }

                random = generate_random_number();
                
                Message msg;
                read(fdPadreHijo[READ_END], &msg, sizeof(msg));
                write(fd[(i + 1) % n][WRITE_END], &msg, sizeof(msg));

                while (1) {
                    read(fd[i][READ_END], &msg, sizeof(msg));
                    printf("Proceso %d, ValorActual: %d\n", getpid(), msg.value);

                    if (msg.value > random) {
                        printf("Game over! Random: %d, ValorActual: %d\n", random, msg.value);
                        msg.game_over = 1;
                        write(fdHijoPadre[WRITE_END], &msg, sizeof(msg));
                        write(fd[(i + 1) % n][WRITE_END], &msg, sizeof(msg));
                        break;
                    } else {
                        msg.value++;
                        write(fd[(i + 1) % n][WRITE_END], &msg, sizeof(msg));
                    }
                }
                exit(0);
            } else {
                close(fdPadreHijo[WRITE_END]);
                close(fdHijoPadre[READ_END]);
                close(fdHijoPadre[WRITE_END]);
                close(fdPadreHijo[READ_END]);

                Message msg;
                while (1) {
                    read(fd[i][READ_END], &msg, sizeof(msg));
                    printf("Proceso %d, ValorActual: %d\n", getpid(), msg.value);
                    if (msg.game_over) {
                        write(fd[(i + 1) % n][WRITE_END], &msg, sizeof(msg));
                        printf("Me voy, recibí un game_over. Mi PID=%d\n", getpid());
                        break;
                    }
                    msg.value++;
                    write(fd[(i + 1) % n][WRITE_END], &msg, sizeof(msg));
                }
                exit(0);
            }
        }
    }

    close(fdPadreHijo[READ_END]);
    close(fdHijoPadre[WRITE_END]);

    Message msg = {mensajeInicial, 0};
    write(fdPadreHijo[WRITE_END], &msg, sizeof(msg));

    read(fdHijoPadre[READ_END], &msg, sizeof(msg));
    printf("El valor final es %d\n", msg.value);

    for (int i = 0; i < n; i++) {
        close(fd[i][READ_END]);
        close(fd[i][WRITE_END]);
        waitpid(children[i], &status, 0);
    }

    close(fdPadreHijo[WRITE_END]);
    close(fdHijoPadre[READ_END]);
    free(children);
    return 0;
}

