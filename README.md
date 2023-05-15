<!DOCTYPE html>
<html>

<head>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }

        h1 {
            color: #333;
            text-decoration: underline;
        }

        h2 {
            color: #666;
        }

        p {
            margin-bottom: 10px;
        }

        ul {
            list-style-type: disc;
            margin-left: 20px;
        }
    </style>
</head>

<body>
    <h1>Shell Program Execution Flow</h1>
    <p>This document outlines the execution flow of a shell program, describing the sequence of steps involved in processing user commands and executing them accordingly.</p>

    <h2>Execution Flow:</h2>
    <ol>
        <li>
            <h3>Start:</h3>
            <ul>
                <li>Initialize the shell program.</li>
                <li>Set up necessary data structures and variables.</li>
            </ul>
        </li>
        <li>
            <h3>Display prompt:</h3>
            <ul>
                <li>Print the shell prompt to the user.</li>
                <li>Indicate that the shell is ready to accept input.</li>
            </ul>
        </li>
        <li>
            <h3>Read command line:</h3>
            <ul>
                <li>Wait for the user to enter a command line input.</li>
                <li>Read the input from the user.</li>
            </ul>
        </li>
        <li>
            <h3>Check if command is a built-in:</h3>
            <ul>
                <li>Compare the entered command with a list of built-in commands (cd, exit, setenv, unsetenv, env, alias).</li>
                <li>Determine if the entered command is a built-in command.</li>
            </ul>
        </li>
        <li>
            <h3>If built-in, execute built-in:</h3>
            <ul>
                <li>If the entered command is a built-in command, execute the corresponding functionality.</li>
                <li>Perform the necessary actions for the built-in command.</li>
            </ul>
        </li>
        <li>
            <h3>If not built-in, check if command exists in PATH:</h3>
            <ul>
                <li>If the entered command is not a built-in command, check if it exists in the system's PATH variable.</li>
                <li>Search for the command executable in the directories specified in the PATH.</li>
            </ul>
        </li>
        <li>
            <h3>If command exists, fork and execute command:</h3>
            <ul>
                <li>If the command exists in the PATH, create a child process using the fork system call.</li>
                <li>In the child process, execute the command using the exec system call.</li>
            </ul>
        </li>
        <li>
            <h3>Wait for child process to complete:</h3>
            <ul>
                <li>In the parent process, wait for the child process to complete its execution.</li>
                <li>Suspend the execution of the parent process until the child process finishes.</li>
            </ul>
        </li>
        <li>
            <h3>Display prompt:</h3>
            <ul>
                <li>After the command execution is complete, display the shell prompt again.</li>
                <li>Indicate that the shell is ready to accept new commands.</li>
            </ul>
		</li>
		<li>
            <h3>Repeat:</h3>
            <ul>
                <li>Go back to step 3 and repeat the process to handle the next command.</li>
           </ul>
		   <ul>
		    <p/>
                <li>By following this execution flow, the shell program can effectively handle user commands,
			execute built-in functionalities, and execute external commands found in the system's PATH.</li>
           </ul>
		
		    
		</li>

