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

/* =====count_chars()===== <br>
arguments: string s and character/string c <br>
description: uses a for loop to parse through s and compares each character to c <br>
returns: number of instances of the character, c, in the string, s
*/

/* =====trim()===== <br>
description: deletes all spaces from string
*/

/* =====parse_args()===== <br>
arguments: string line and character/string sep <br>
description: cuts off line by sep, and puts that component into args string array <br>
returns: array of strings where each slot is an arg
*/

/* =====fork_and_run()===== <br>
arguments: string array of arguments <br>
description: forks, child will execvp the command, parent waits for child
*/

/* =====exit_shell()===== <br>
   description: creates an array of strings where the first element is the "exit" string <br>
   execvp exit using this information
*/

/* =====cd()===== <br>
   arguments: string s <br>
   description: changes directory based on the argument <br>
   (separated function for the sake of formatting)
*/

/* ======simple_pipe()====== <br>
   arguments: string s <br>
   description: parses through full piping command until it reaches | <br>
				goes through the commands again from beginning and collects everything <br>
   				redirects the command and then executes it so that the output of the command before | is the input of the command after
*/

/* ======simple_redirect()====== <br>
   arguments: string s, int x <br>
   description: parses through full piping command until it reaches > or < <br>
				runs beginning command <br>
   				redirects output of first command into specified file <br>
				resets stdout
*/

/* =====get_and_run()====== <br>
arguments: string s <br>
description: receives commands from user, and goes through the string <br>
					   while there are more args, run those <br>
						 exit and cd run without forking
*/

