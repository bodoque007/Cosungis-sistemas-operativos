#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


/*
Modificar el programa anterior para que cumpla con las siguientes condiciones: 1) Padre cree dos
procesos hijos en lugar de uno, y 2) se respete esta nueva secuencia de mensajes entre los tres
procesos.
1. Padre envía a Hijo_1 el valor 0,
2. Hijo_1 envía a Hijo_2 el valor 1,
3. Hijo_2 envía a Padre el valor 2,
4. Padre envía a Hijo_1 el valor 3,
...hasta llegar al valor 50.
                USAR PIPES
                Nota: El programa anda como es esperado pero me falta hacer close() a los end pipes que cada proceso no va a utilizar (buena practica), pero paja, me acordare en el parcial.
*/

#define READ_END 0
#define WRITE_END 1
#define NUM 50

int fd_parent_child[2];
int fd_child_child[2];
int fd_child_parent[2];


void child1_process() {
    int k;
    while(1) {
        read(fd_parent_child[READ_END], &k, sizeof(k));
        printf("Child 1 read %d\n", k);
        if (k >= NUM) {
            break;
        }
        k++;
        write(fd_child_child[WRITE_END], &k, sizeof(k));
    }
    // Last write to make sure child 2 exits
    write(fd_child_child[WRITE_END], &k, sizeof(k));
    exit(0);
}

void child2_process() {
    int k;
    while(1) {
        read(fd_child_child[READ_END], &k, sizeof(k));
        printf("Child 2 read %d\n", k);
        if (k >= NUM) {
            break;
        }
        k++;
        write(fd_child_parent[WRITE_END], &k, sizeof(k));
    }
    exit(0);
}

int main() {
    pipe(fd_parent_child);
    pipe(fd_child_child);
    pipe(fd_child_parent);

    pid_t child1_pid = fork();
    if (child1_pid == 0) {
        child1_process();
    } else {
        pid_t child2_pid = fork();
        if (child2_pid == 0) {
            child2_process();
        } else {
            int k = 0;
            while(k < 50) {
                write(fd_parent_child[WRITE_END], &k, sizeof(k));
                read(fd_child_parent[READ_END], &k, sizeof(k));
                k++;
                printf("Parent read %d\n", k);
            }
            // Last write to make sure child 1 exits.
            write(fd_parent_child[WRITE_END], &k, sizeof(k));
        }
    }
    wait(NULL);
    wait(NULL);
    return 0;
}