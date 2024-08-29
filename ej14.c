/*
    PROGRAMA EJERCICIO 12
    int result;
void proceso_izquierda() {
    result = 0;
    while (true) {
        bsend(pid_derecha, result);
        result = cómputo_muy_difícil_1();
    }
}
void proceso_derecha() {
    while(true) {
        result = cómputo_muy_difícil_2();
        int left_result = breceive(pid_izquierda);
        printf(" %s %s", left_result, result);
    }
}
*/


/*
Un sistema operativo provee las siguientes llamadas al sistema para efectuar comunicación entre
procesos mediante pasaje de mensajes.
bool send(pid dst, int *msg) Envía al proceso dst el valor del puntero.
Retorna false si la cola de mensajes
estaba llena.
bool receive(pid src, int *msg) Recibe del proceso src el valor del puntero.
Retorna false si la cola de mensajes
estaba vacía.
a) Modificar el programa del ejercicio 12 para que utilice estas llamadas al sistema
*/


int result;
void proceso_izquierda() {
    result = 0;
    while (true) {
        while(!send(pid_derecha, &result)) sleep(0.5);
        result = cómputo_muy_difícil_1();
    }
}

int left_result;
void proceso_derecha() {
    while(true) {
        result = cómputo_muy_difícil_2();
        while(!receive(pid_izquierda, &left_result)) sleep(0.5);
        printf(" %s %s", left_result, result);
    }
}