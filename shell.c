#include "shell.h"

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

/* trim()
   description: deletes all spaces from string
*/
void trim(char * arr)
{
  char* i = arr;
  char* j = arr;
  while(*j){
    *i = *j++;
    if(*i != ' '){
      i++;
    }
  }
  *i = 0;
}

/* parse_args()
   arguments: string line and character/string sep
   description: cuts off line by sep, and puts that component into args string array
   returns: array of strings where each slot is an arg
*/
char ** parse_args( char * line, char * sep ) {
  int num = count_chars(line,sep);
  //printf("num of \"%s\" in \"%s\" = %d\n", sep, line, num);
  char ** args = malloc((num+1) * sizeof(char *));
  //char ** args = malloc(sizeof(line));
  char * flag = NULL;
  
  int i = 0;
  while ((flag = strsep(&line, sep))) {
    if (strcmp(flag, "") != 0){
      //trim(flag);
      //printf("flag %s\n", flag);
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
  int replace = 0;
  
  //parent
  if (f){
    int status;
    f = wait(&status);
    //printf("\nPARENT:\n");
    //printf("child %d finished [%s] command\n", f, args[0] );
    //printf("parent %d has finished\n", getpid() );
  }

  //child
  else{
    //printf("\nCHILD:\n");
    //printf("pid: %d\n", getpid() );

    /*
    int stdout_fd = dup(1);
    //printf("args[0] = %s\n", args[0]);
    if (args[1] != NULL && strcmp(args[1], ">") == 0){
      char ** arr = malloc(256 * sizeof(char *));
      arr[0] = args[0];
      arr[1] = NULL;
      int fd = open(args[2], O_CREAT | O_WRONLY, 0644);
      dup2(fd,1);
      replace = 1;
      //printf("args[0] = %s\n", args[0]);
      execvp(args[0], arr);
    }
    if (replace == 1){
      dup2(stdout_fd,1);
    }
    */
    //else{
      execvp(args[0], args);
      //}
  }
}

/* exit()
   description: creates an array of strings where the first element is the "exit" string
   execvp exit using this information
*/
void exit_shell() {
  char * args[1];
  args[0] = "exit";
  execvp("exit",args);
}

/* cd()
   arguments: string s
   description: changes directory based on the argument
   (separated function for the sake of formatting)
*/
void cd(char * s) {
  chdir(s);
}

/* simple_pipe()
   arguments: string s
   description: parses through full piping command until it reaches |
   goes through the commands again from beginning and collects everything
   redirects the command and then executes it so that the output of the command before | is the input of the command after
*/
void simple_pipe(char ** s) {
  int i, j;
  for (i = 0; s[i]; i++) {
    char * temp = malloc(256 * sizeof(char *));
    *temp = s[i][0];
    if (strcmp(temp,"|") == 0) {
      
      char first[256] = "";
      for (j = 0; j < i; j++) {
        strcat(first, s[j]);
        strcat(first, " ");
      }
      //printf("first part: %s", first);
      
      FILE *fp = popen(first, "r");
      int fd = fileno(fp);
      dup2(fd, 0);
      close(fd);
      s += i + 1;
      execvp(s[0], s);
    }		
  }
}

/* ======simple_redirect()======
   arguments: string s, int x
   description: parses through full piping command until it reaches > or <
   runs beginning command
   redirects output of first command into specified file
   resets stdout
*/
void simple_redirect(char ** args, int x) {
  if (x == 1){
    char ** arr = malloc(256 * sizeof(char *));
    arr[0] = args[0];
    arr[1] = NULL;
    int fd = open(args[2], O_CREAT | O_WRONLY, 0644);
    dup2(fd,1);
    //printf("args[0] = %s\n", args[0]);
    execvp(args[0], arr);
  }
  else if (x == 2){
    char ** arr = malloc(256 * sizeof(char *));
    arr[0] = args[0];
    arr[1] = NULL;
    int fd = open(args[2], O_CREAT | O_RDONLY, 0644);
    dup2(fd,0);
    //printf("args[0] = %s\n", args[0]);
    execvp(args[0], arr);    
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
    //printf("received %s\n", s);

    char ** commands = parse_args(s, ";");
    int num_commands = count_chars(s, ";"); //brute fix

    /*
    int i;
    int function = 0;
    printf("num_commands = %d\n", num_commands);
    for (i = 0; i<num_commands+1; i++) {
      printf("===RAN===\n");
      printf("command = %s", commands[i]);
      if (strchr(commands[i],'|')==0) {
	function = 1;
      }
      else if (strchr(commands[i],'>')==0) {
	function = 2;
      }
      else if (strchr(commands[i],'<')==0) {
	function = 3;
      }
    }
    */
    
    while (*commands && num_commands+1 >= 0){
      //printf("command: %s\n", *commands);
      
      if (strchr(*commands,'|')){
	char ** command = parse_args(*commands, "|");
	simple_pipe(command);
	break;
      }
      else if (strchr(*commands,'>')){
	char ** command = parse_args(*commands, ">");
	int stdout_fd = dup(1);
	simple_redirect(command, 1);
	dup2(stdout_fd,1);
	break;
      }
      else if (strchr(*commands,'<')){
	char ** command = parse_args(*commands, ">");
	int stdin_fd = dup(0);
	simple_redirect(command, 2);
	dup2(stdin_fd,0);
	break;
      }
      
      /*
	int function = 0;
	if (strchr(*commands,'|')) {
	function = 1;
	printf("1\n");
	}
	else if (strchr(*commands,'>')) {
	function = 2;
	printf("2\n");
	}
	else if (strchr(*commands,'<')) {
	function = 3;
	printf("3\n");
	}
      */
      
      char ** command = parse_args(*commands, " ");
      
      /*
	if (function != 0) {
	if (function == 1) {
	simple_pipe(command);
	}
	}
      */

      /*
	printf("function: %d\n", function);
	if (function == 1){
	printf("duh");
	simple_pipe(command);
	}
      else {
      */
      //printf("dumb");
      if (strcmp(*command,"exit")==0) {
	exit_shell();
	return;	
      }
      else if (strcmp(*command,"cd")==0) {
	cd(command[1]);
      }
      else if (command != NULL){
	fork_and_run(command);
      }
      commands++;
      num_commands--;
      //}
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
