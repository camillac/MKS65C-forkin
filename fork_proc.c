#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


int main(){
  printf("PARENT PID: %d\n", getpid());

  int status;
  pid_t f1 = fork();
  pid_t f2;
  // if parent, create second child
  if (f1) {
    f2 = fork();
  }

  // if child of parent
  if (f1 == 0 || f2 == 0) {
    srand(getpid());
    int t = (rand() % 5) + 5; // rand range [5,20]
    printf("\tchild pid: %d\ttime: %d\n", getpid(), t);
    sleep(t);

    printf("\tCHILD %d IS DONE\n", getpid());
    return t;
  }
  // if parent
  else {
    // wait until a child process is done
    int cpid = wait(&status);
    int slept = WEXITSTATUS(status);
    printf("CHILD %d SLEPT FOR %d SECONDS\n", cpid, slept);
    printf("PARENT %d IS DONE!!!!!!!!!\n", getpid());
  }
  return 0;

}
