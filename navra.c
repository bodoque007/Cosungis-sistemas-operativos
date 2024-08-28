

/*
Un nuevo sistema operativo ofrece las siguientes llamadas al sistema para efectuar comunicación
entre procesos:
void bsend(pid dst, int msg) Envía el valor msg al proceso dst.
int breceive(pid src) Recibe un mensaje del proceso src.
Ambas llamadas al sistema son bloqueantes y la cola temporal de mensajes es de capacidad cero. A
su vez, este sistema operativo provee la llamada al sistema pid get_current_pid() que devuelve el
process id del proceso que invoca dicha llamada
Escribir un programa que cree un segundo proceso, para luego efectuar la siguiente secuencia de
mensajes entre ambos:
1. Padre envía a Hijo el valor 0,
2. Hijo envía a Padre el valor 1,
3. Padre envía a Hijo el valor 2,
4. Hijo envía a Padre el valor 3,
etc...
*/


void child_read_and_receive(pid_t parent) {
    int k = breceive(parent);
    bsend(parent, k + 1);
}

int main() {
    pid_t pid = fork();
    pid_t parent = getpid();
    if (pid == 0) {
        // getpid() is parent'
        while(1) child_read_and_receive(parent);
    } else {
        int k = 0;
        while(1) {
            bsend(pid, k);
            k = breceive(pid);
            k++;
        }
    }
}