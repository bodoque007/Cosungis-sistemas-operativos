// Ej 2
#define KE_RUNNING 0
#define KE_READY 1
#define KE_BLOCKED 2
#define KE_NEW 3


struct PCB {
int STAT; // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
int P_ID; // process ID
int PC; // valor del PC del proceso al ser desalojado
int RO; // valor del registro R0 al ser desalojado
// Ri for i in range [1, 15)
int R15; // valor del registro R15 al ser desalojado
int CPU_TIME; // tiempo de ejecución del proceso
};

·=·; // asignación entre registros y memoria
int ke_current_user_time(); // devuelve el valor del cronómetro
void ke_reset_current_user_time(); // resetea el cronómetro
void ret(); // desapila el tope de la pila y reemplaza el PC
void set_current_process(int pid) // asigna al proceso con el pid como el siguiente
a ejecutarse

void Ke_context_switch(PCB* pcb_0, PCB* pcb_1) {
    pcb_0->STAT =  KE_READY; // Not KE_RUNNING anymore. Set to ready for next time its loaded on the CPU
    pcb_0->CPU_TIME += ke_current_user_time();
    R0 = pcb_1->RO;
    ...
    R15 = pcb_1->R15;

    pcb_1->STAT = KE_RUNNING;
    ke_reset_current_user_time();
    set_current_process(pcb_1->P_ID);
    ret()
}

// Ej 3
/*
    Diferencias entre syscall y funcion de biblioteca:
        La principal diferencia es que una syscall corre en privilegio de kernel (0), mientras que una funcion de biblioteca corre en privilegio de usuario.
        Esto implica que cuando una syscall es llamada, muy posiblemente esta requiera un cambio de privilegios de user mode a kernel mode.

*/