#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*
Utilizando únicamente la llamada al sistema fork(), escribir un programa tal que construya un
árbol de procesos que represente la siguiente genealogía: Abraham es padre de Homero, Homero es
padre de Bart, Homero es padre de Lisa, Homero es padre de Maggie. Cada proceso debe imprimir
por pantalla el nombre de la persona que representa.
*/

/*
Modificar el programa anterior para que cumpla con las siguientes condiciones: 1) Homero termine
sólo después que terminen Bart, Lisa y Maggie, y 2) Abraham termine sólo después que termine
Homero.
*/
// Lo resolvi incluso un poco mas fuerte, forzando a que primero termine ("nazca") Bart, luego Lisa y finalmente Maggie.
// Un while pid_t child_pid, wpid;
// int status = 0; ((wpid = wait(&status)) > 0); al final del codigo de homero lograria lo que se pide.
int main(int argc, char const *argv[]) {
    pid_t pid = fork();
    // puaj anidado pero no voy a tryhardearla
    if (pid == 0) {
        write(1, "Homero\n", 8);
        pid_t pid = fork();
        if (pid == 0) {
            write(1, "Bart\n", 6);
            exit(EXIT_SUCCESS);
        } else {
            waitpid(pid, NULL, 0);
            pid_t pid = fork();
            if (pid == 0) {
                write(1, "Lisa\n", 6);
                exit(EXIT_SUCCESS);
            } else {
                waitpid(pid, NULL, 0);
                pid_t pid = fork();
                if (pid == 0) {
                    write(1, "Maggie\n", 8);
                    exit(EXIT_SUCCESS);
                }
            }
        }
    } else {
        write(1, "Abraham!\n", 9);
        waitpid(pid, NULL, 0);
    }
    exit(EXIT_SUCCESS);
}