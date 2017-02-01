#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
  pid_t rdr,  /* input reader process */
        cmd,  /* command runner process */
        wres; /* wait() result */
  /* pipe for passing input from rdr to cmd */
  int pipefd[2] = {0};
  /* command and args to pass to execvp() */
  char *command = "cat";
  char *tabcat[] = { "cat", "-e", NULL };
  /* end of input marker */
  char *endinp = "END\n";

  /* create a pipe: 
     - read end's fd will be pipefd[0], 
     - write end's fd will be pipefd[1] */
  pipe(pipefd);

  cmd = fork();
  if (!cmd) {  /* COMMAND RUNNER PROCESS */
    dup2(pipefd[0],0); /* set stdin to pipe's read end */
    close(pipefd[1]);  /* close pipe's write end */
    /* exec command (will read from stdin) */
    execve("/bin/cat", tabcat, NULL);
  }

  rdr = fork();
  if (!rdr) {   /* INPUT READER PROCESS */
    close(pipefd[0]); /* close pipe's read end */

    /* read input from stdin until a line containing only
       the end of input marker is found */
    char buf[1024];
    while (fgets(buf,sizeof(buf),stdin)) {
      /* break when end of input marker is read */
      if (!strcmp(buf,endinp)) break;
      /* write data to pipe */
      write(pipefd[1],buf,strlen(buf));
    }
    return 0;
  }

  /* PARENT PROCESS */

  close(pipefd[0]); /* close pipe's read end */
  close(pipefd[1]); /* close pipe's write end */

  /* wait for both children to exit */
  do {
    wres = wait(NULL);
    if (wres == rdr) rdr = 0;
    if (wres == cmd) cmd = 0;
  } while (rdr || cmd);

  return 0;
}