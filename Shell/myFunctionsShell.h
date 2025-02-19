#ifndef MYFUNCTIONSSHELL_H
#define MYFUNCTIONSSHELL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/wait.h>
#endif

#define SIZE_BUFF 256

/**
 * Reads a line of input from the user.
 * 
 * This function dynamically allocates memory to store user input.
 * The caller is responsible for freeing the allocated memory.
 * 
 * @return A dynamically allocated string containing user input.
 */
char *getInputFromUser();

/**
 * Splits a string into individual tokens based on whitespace.
 *
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 *
 * @param input A pointer to the string to be split.
 *
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 *
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 *
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char **splitArguments(char *);

/**
 * Prints the current working directory along with the username and hostname.
 *
 * This function retrieves and prints the current directory, the username, and the hostname of the system.
 * The output is color-coded for better visibility.
 */
void getLocation();

/**
 * Logs out of the shell if the command "exit" is entered.
 *
 * This function checks if the provided input is "exit" and terminates the shell session if true.
 *
 * @param input The command entered by the user.
 */
void logout(char *input);

/**
 * Prints a string to the terminal.
 *
 * This function prints each argument passed to it, separating words with spaces.
 * If no argument is provided, it prints an empty line.
 *
 * @param arguments An array of strings to be printed.
 */
void echo(char **arguments);

/**
 * Changes the current working directory.
 *
 * This function attempts to change to the specified directory.
 * If the directory does not exist, an error message is displayed.
 *
 * @param arguments An array containing the "cd" command and the target directory.
 */
void cd(char **);

/**
 * Copies a file from source to destination.
 *
 * This function reads data from a source file and writes it to a destination file.
 * If the source file cannot be read or the destination file cannot be created, an error message is displayed.
 *
 * @param arguments An array containing the "cp" command, the source file, and the destination file.
 */
void cp(char **arguments);

/**
 * Lists the contents of the current directory.
 *
 * This function retrieves and prints the names of all files and directories in the current directory.
 */
void get_dir();

/**
 * Deletes a specified file.
 *
 * This function removes a file from the filesystem if it exists.
 * If the file does not exist or cannot be deleted, an error message is displayed.
 *
 * @param arguments An array containing the "delete" command and the filename.
 */
void delete(char **arguments);

/**
 * Executes a system command.
 *
 * This function forks a new process to execute an external system command using execvp().
 * If the command execution fails, an error message is displayed.
 *
 * @param arguments An array containing the command and its parameters.
 */
void systemCall(char **arguments);

/**
 * Connects two commands using a pipe.
 *
 * This function executes two commands such that the output of the first command becomes the input of the second command.
 * It uses pipe() and fork() to achieve inter-process communication.
 *
 * @param argv1 The first command to execute.
 * @param argv2 The second command to execute, which takes the output of the first command as input.
 */
void mypipe(char **, char **);

/**
 * Moves a file from source to destination.
 *
 * This function renames a file to a new location, effectively moving it.
 * If the move operation fails, an error message is displayed.
 *
 * @param args An array containing the "move" command, the source file, and the destination file.
 */
void move(char **args);

/**
 * Appends text to a file.
 *
 * This function takes a string and appends it to the specified file.
 * If the file cannot be opened, an error message is displayed.
 *
 * @param args An array containing the "echoppend" command, the text, and the filename.
 */
void echoppend(char **args);

/**
 * Writes text to a file (overwriting existing content).
 *
 * This function takes a string and writes it to the specified file, replacing any existing content.
 * If the file cannot be opened, an error message is displayed.
 *
 * @param args An array containing the "echowrite" command, the text, and the filename.
 */
void echowrite(char **args);

/**
 * Reads and displays the content of a file.
 *
 * This function opens a file in read mode and prints its content to the terminal.
 * If the file cannot be opened, an error message is displayed.
 *
 * @param args An array containing the "read" command and the filename.
 */
void _read(char **args);

/**
 * Counts words, lines, or characters in a file.
 *
 * This function analyzes a file and counts either lines (-l), words (-w), or characters (-c),
 * depending on the user's option.
 * If the file cannot be opened, an error message is displayed.
 *
 * @param args An array containing the "wordCount" command, the option, and the filename.
 */
void wordCount(char **args);

#endif 
