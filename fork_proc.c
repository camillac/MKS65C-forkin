#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(){
  printf("PARENT PID: %d\n", getpid());
  pid_t f1 = fork();
  pid_t f2;
  int * fd = calloc(1, sizeof(int));
  int file_num = open("time.txt", O_CREAT); // create time.txt
  close(file_num);

  // if parent, create second child
  if (!f1) {
    f2 = fork();
  }
  // if child of parent
  if (f1 == 0 || f2 == 0) {
    srand(getpid());
    int t = (rand() % 15) + 5; // rand range [5,20]
    printf("\tchild pid: %d\ttime: %d\n", getpid(), t);
    sleep(t);

    // write time slept into time.txt
    file_num = open("time.txt", O_WRONLY);
    write(file_num, &t, sizeof(int));
    close(file_num);

    printf("\tCHILD %d IS DONE\n", getpid());
    exit(0);
  }
  // if parent
  else {
    // wait until a child process is done
    int stat;
    int cpid = wait(&stat);

    // read time slept from time.txt
    file_num = open("time.txt", O_RDONLY);
    read(file_num, fd, sizeof(int));

    printf("CHILD %d SLEPT FOR %d SECONDS\n", cpid, fd[0]);
    printf("PARENT IS DONE!!!!!!!!!\n");
    free(fd);
  }
  return 0;

}
