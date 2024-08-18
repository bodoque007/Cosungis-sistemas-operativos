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


int main(int argc, char const *argv[]) {
    pid_t pid = fork();
    // puaj anidado pero no voy a tryhardearla
    if (pid == 0) {
        write(1, "Homero\n", 8);
        pid_t pid = fork();
        if (pid == 0) {
            write(1, "Bart\n", 6);
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                write(1, "Lisa\n", 6);
            } else {
                pid_t pid = fork();
                if (pid == 0) {
                    write(1, "Maggie\n", 8);
                }
            }
        }
    } else {
        write(1, "Abraham!\n", 9);
    }
    exit(EXIT_SUCCESS);
}