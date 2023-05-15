
Shell Program Execution Flow
============================

This document outlines the execution flow of a shell program, describing the sequence of steps involved in processing user commands and executing them accordingly.

Execution Flow:
---------------

1.  ### Start:
    
    *   Initialize the shell program.
    *   Set up necessary data structures and variables.
2.  ### Display prompt:
    
    *   Print the shell prompt to the user.
    *   Indicate that the shell is ready to accept input.
3.  ### Read command line:
    
    *   Wait for the user to enter a command line input.
    *   Read the input from the user.
4.  ### Check if command is a built-in:
    
    *   Compare the entered command with a list of built-in commands (cd, exit, setenv, unsetenv, env, alias).
    *   Determine if the entered command is a built-in command.
5.  ### If built-in, execute built-in:
    
    *   If the entered command is a built-in command, execute the corresponding functionality.
    *   Perform the necessary actions for the built-in command.
6.  ### If not built-in, check if command exists in PATH:
    
    *   If the entered command is not a built-in command, check if it exists in the system's PATH variable.
    *   Search for the command executable in the directories specified in the PATH.
7.  ### If command exists, fork and execute command:
    
    *   If the command exists in the PATH, create a child process using the fork system call.
    *   In the child process, execute the command using the exec system call.
8.  ### Wait for child process to complete:
    
    *   In the parent process, wait for the child process to complete its execution.
    *   Suspend the execution of the parent process until the child process finishes.
9.  ### Display prompt:
    
    *   After the command execution is complete, display the shell prompt again.
    *   Indicate that the shell is ready to accept new commands.
10.  ### Repeat:
    
    *   Go back to step 3 and repeat the process to handle the next command.
    
    *   By following this execution flow, the shell program can effectively handle user commands, execute built-in functionalities, and execute external commands found in the system's PATH.