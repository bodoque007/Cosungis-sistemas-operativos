#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



void handleSIGURG() {
  printf("ya va!\n");
}

int main(int argc, char *argv[])
{
  pid_t pid = fork();
  if (pid == 0) {
    signal(handleSIGURG, SIGURG);
    int i = 0;
    while (i < 4) {
      pause();
      i++;
    }
    pid_t parent = getppid();
    kill(parent, SIGINT);
    execvp(argv[1], &argv[1]);
    printf("hai\n");
    } else {
      int i = 0;
      while (i < 4) {
        sleep(1);
        printf("sup!\n");
        kill(pid, SIGURG);
        i++;
      }
  }
  // Buena practica ?)
  wait(NULL);
  return 0;
}
