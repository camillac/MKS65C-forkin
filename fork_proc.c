#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(){
  printf("PARENT PID: %d\n", getpid());
  int f1 = fork();
  int f2;
  if (!f1) {
    f2 = fork();
  }
  if (f1 == 0 || f2 == 0) {
    srand(getpid());
    printf("child pid: %d\n", getpid());
    int t = (rand() % 15) + 5;
    sleep(t);
    printf("CHILD %d IS DONE\n", getpid());
    return t;
  }
  else {
    wait(WIFEXITED);
      printf("PARENT IS DONE!!!!!!!!!\n");
  }

}
