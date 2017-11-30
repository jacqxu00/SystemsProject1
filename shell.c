#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/* count_chars()
   arguments: string s and character/string c
   description: uses a for loop to parse through s and compares each character to c
   returns: number of instances of the character, c, in the string, s
*/
int count_chars(char * s, char * c){
  int i;
  int ans = 0;
  for (i=0; s[i]; i++) {
    char temp[2];
    temp[0] = s[i];
    temp[1] = '\0';
    //printf("s[i] = %c\n", s[i]);
    //printf("s = %s\n", s);
    //printf("c = %s\n", c);
    if (strcmp(temp, c) == 0) {
      ans++;
    }
  }
  return ans;
}

/* parse_args()
   arguments: string line and character/string sep
   description: cuts off line by sep, and puts that component into args string array
   returns: array of strings where each slot is an arg
*/
char ** parse_args( char * line, char * sep ) {
  int num = count_chars(line,sep);
  printf("num of \"%s\" in \"%s\" = %d\n", sep, line, num);
  char ** args = malloc((num+1) * sizeof(char *));
  //char ** args = malloc(sizeof(line));
  char * flag = NULL;
  
  int i = 0;
  while ((flag = strsep(&line, sep))) {
    if (strcmp(flag, "") != 0){
      printf("flag %s\n", flag);
      args[i] = flag;
      i++;
    }
  }
  args[i] = NULL;
  return args;
}

/* fork_and_run()
   arguments: string array of arguments
   description: forks, child will execvp the command, parent waits for child
*/
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

/* get_and_run()
   arguments: string s
   description: receives commands from user, and goes through the string
   while there are more args, run those
   exit and cd run without forking
*/
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

    char ** commands = parse_args(s, ";");
    int num_commands = count_chars(s, ";"); //brute fix
		
    while (*commands && num_commands+1 >= 0){
      printf("command: %s\n", *commands);
      if (count_chars(*commands, ">") > 0){
	char ** redirect = parse_args(*commands, ">");
	//enter stuff here
      }
      char ** command = parse_args(*commands, " ");
      if (strcmp(*command,"exit")==0) {
	char * args[1];
	args[0] = "exit";
	execvp("exit",args);
	return;
      }
      else if (strcmp(*command,"cd")==0) {
	chdir(command[1]);
      }
      else if (command != NULL){
	fork_and_run(command);
      }
      commands++;
      num_commands--;
      
    }
    printf("\n--\n\nenter another command: ");
  }
}

/* simple_pipe()
   arguments: string s
   description: receives full piping command and separates by the | char
   creates a pipe where the first sub-command writes, the second reads
   run the first sub-command then the second takes it in and runs
*/
void simple_pipe(char * s) {
  
}

/* simple_redirect()
   arguments: 
   description: 
*/
void simple_redirect() {
  int fd = open(foo.txt, O_CREAT | O_WRONLY, 0644);
  int stdout_fd = dup(1);
  dup2(fd,1);
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
