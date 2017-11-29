# Systems Project: Shell

### Features
* takes in one line shell commands from user and runs it
* can run multiple commands on one line if separated by a ";"
* can exit and cd into different directories

### Attempted
* 

### Bugs
* 

### Files & Function Headers:
shell.c receives commands from user and runs them

/* =====count_chars()=====
arguments: string s and character/string c
description: uses a for loop to parse through s and compares each character to c
returns: number of instances of the character, c, in the string, s

/* =====parse_args()=====
arguments: string line and character/string sep
description: cuts off line by sep, and puts that component into args string array
returns: array of strings where each slot is an arg
*/

/* =====fork_and_run()=====
arguments: string array of arguments
description: forks, child will execvp the command, parent waits for child
*/

/* =====get_and_run()======
arguments: string s
description: receives commands from user, and goes through the string
					   while there are more args, run those
						 exit and cd run without forking
*/