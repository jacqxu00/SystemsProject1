#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

char ** parse_args( char * line, char * sep ) {
  char ** args = malloc(6 * sizeof(char *));
  char * flag = NULL;
  
  int i = 0;
  while ((flag = strsep(&line, sep))) {
    args[i] = flag;
    i++;
  }
  args[i] = NULL;
  return args;
}

void fork_and_run(char ** args){
  int f = fork();

  //parent
  if (f){
    int status;
    f = wait(&status);
    printf("\nPARENT:\n");
    printf("child %d finished [%s] command\n", f, args[0] );
    printf("parent %d has finished\n", getpid() );
  }

  //child
  else{
    printf("\nCHILD:\n");
    printf("pid: %d\n", getpid() );
    execvp(args[0], args);
  }
}

void get_and_run(char * s){
  printf("enter a command: ");
  while (fgets(s, 256, stdin)){
    s = strsep(&s, "\n");
    printf("received %s\n", s);

    /*
    char * temp = s;
    while (temp){
      if (*temp == ";" && *(temp-1) == " "){
	strcpy(temp-1, "");
      }
      if (*temp == ";" && *(temp+1) == " "){
	strcpy(temp+1, "");
      }
      temp++;
    }
    */

    //currently works with no spaces (ex: "ls;ls")
    char ** commands = parse_args(s, ";");

    while (commands){
      printf("command: %s", *commands);
      char ** command = parse_args(*commands, " ");
      fork_and_run(command);
      commands++;
    }
    printf("\n--\n\nenter another command: ");
  }
}

int main() {

  /*
  char line[] = "ls -a -l --color";
  char ** args = parse_args( line , " " );
  forkandrun(args);
  */
  
  char * s = malloc(256 * sizeof(char *));
  get_and_run(s);
  
  return 0;
}
