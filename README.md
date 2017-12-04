# Systems Project: Shell

### Features
* takes in one line shell commands from user and runs it
* can run multiple commands on one line if separated by a ";"
* can exit and cd into different directories

### Attempted
* piping
* redirection (both ways)

### Bugs
* occasionally there are random segfaults/incorrect mallocs and we couldn't figure it out

### Files & Function Headers:
shell.c receives commands from user and runs them

/* =====count_chars()=====
arguments: string s and character/string c
description: uses a for loop to parse through s and compares each character to c
returns: number of instances of the character, c, in the string, s

/* =====trim()=====
description: deletes all spaces from string

/* =====parse_args()=====
arguments: string line and character/string sep
description: cuts off line by sep, and puts that component into args string array
returns: array of strings where each slot is an arg
*/

/* =====fork_and_run()=====
arguments: string array of arguments
description: forks, child will execvp the command, parent waits for child
*/

/* =====exit_shell()=====
   description: creates an array of strings where the first element is the "exit" string
   execvp exit using this information
*/

/* =====cd()=====
   arguments: string s
   description: changes directory based on the argument
   (separated function for the sake of formatting)
*/

/* ======simple_pipe()======
   arguments: string s
   description: parses through full piping command until it reaches |
				goes through the commands again from beginning and collects everything
   				redirects the command and then executes it so that the output of the command before | is the input of the command after

*/

/* ======simple_redirect()======
   arguments: string s, int x
   description: parses through full piping command until it reaches > or <
				runs beginning command
   				redirects output of first command into specified file
				resets stdout

*/

/* =====get_and_run()======
arguments: string s
description: receives commands from user, and goes through the string
					   while there are more args, run those
						 exit and cd run without forking
*/

