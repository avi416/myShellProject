#include "myFunctionsShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *getInputFromUser()
{
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    // Get input from user
    read = getline(&input, &len, stdin);

    // Handle errors or empty input
    if (read == -1)
    {
        free(input);
        return NULL;
    }

    // Remove newline character
    input[strcspn(input, "\n")] = 0;

    return input;
}




char **splitArguments(char *input)
{
    if (!input)
        return NULL;
    
    int capacity = 10;
    char **arguments = malloc(capacity * sizeof(char*));
    if (!arguments)
    {
        perror("malloc failed");
        return NULL;
    }
    
    int i = 0;                  
    int in_quotes = 0;         
    char buffer[256] = {0};     


    char *token = strtok(input, " ");
    
    while (token != NULL)
    {
        if (!in_quotes && token[0] == '\"')
        {
            in_quotes = 1;
        
            strcpy(buffer, token + 1);
            
      
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\"')
            {
               
                buffer[len - 1] = '\0';
                
               
                arguments[i] = malloc(strlen(buffer) + 1);
                strcpy(arguments[i], buffer);
                i++;
                in_quotes = 0;
                buffer[0] = '\0';  
            }
        }
          
        else if (in_quotes)
        {
            
            strcat(buffer, " ");
            strcat(buffer, token);
            
      
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\"')
            {
                buffer[len - 1] = '\0';  
                arguments[i] = malloc(strlen(buffer) + 1);
                strcpy(arguments[i], buffer);
                i++;
                in_quotes = 0;
                buffer[0] = '\0'; 
            }
        }
       
        else
        {
          
            arguments[i] = malloc(strlen(token) + 1);
            strcpy(arguments[i], token);
            i++;
        }
        
       
        if (i >= capacity - 1)
        {
            capacity *= 2;
            char **temp = realloc(arguments, capacity * sizeof(char*));
            if (!temp)
            {
                perror("realloc failed");
                
                
                free(arguments);
                return NULL;
            }
            arguments = temp;
        }
        
        token = strtok(NULL, " ");
    }
    
  
    arguments[i] = NULL;
    return arguments;
}




/**
 * Prints the current working directory along with the username and hostname.
 */
void getLocation()
{
    char location[256];
    char *user = getenv("USER");
    char host[256];

    if (user == NULL)
    {
        user = getenv("USERNAME");
        if (user == NULL)
        {
            user = "unknown";
        }
    }

    if (gethostname(host, sizeof(host)) != 0)
    {
        strcpy(host, "unknown");
    }

    if (getcwd(location, sizeof(location)) == NULL)
    {
        perror("getcwd failed");
        return;
    }

  
    printf("\033[1;35m(MyShell)\033[0m ");
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", user, host, location);
    fflush(stdout);
}


int isExitValue(char *args)
{
    if (args == NULL)
        return 0;

    // Trim whitespace if needed
    while (*args == ' ') args++;

    return (strcmp(args, "exit") == 0);
}






void logout(char *input)
{
    if (input)
        free(input);

    puts("Exiting shell... Goodbye!");
    exit(EXIT_SUCCESS);
}


void systemCall(char **arguments)
{
    if (arguments[0] == NULL)
    {
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(arguments[0], arguments);

        char fullCommand[256];
        snprintf(fullCommand, sizeof(fullCommand), "/bin/%s", arguments[0]);
        execvp(fullCommand, arguments);

  
        perror("Exec failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
      
        wait(NULL);
    }
    else
    {
        perror("Fork failed");
    }
}




void mypipe(char **argv1, char **argv2)
{
    int fd[2];
    
    // Create a pipe and check for errors
    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        return;
    }

    if (pid1 == 0) // First child process
    {
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd[0]); // Close unused read end
        close(fd[1]); // Close write end after duplication
        execvp(argv1[0], argv1);
        perror("Exec failed"); // Print error if exec fails
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("Fork failed");
        return;
    }

    if (pid2 == 0) // Second child process
    {
        dup2(fd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(fd[1]); // Close unused write end
        close(fd[0]); // Close read end after duplication
        execvp(argv2[0], argv2);
        perror("Exec failed"); // Print error if exec fails
        exit(1);
    }

    // Close pipe ends in parent process
    close(fd[0]);
    close(fd[1]);

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);
}


void move(char **args)
{
    // Validate input arguments
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "Usage: move <source_file> <destination_file>\n");
        return;
    }

    // Attempt to rename (move) the file
    if (rename(args[1], args[2]) == 0)
    {
        printf("File '%s' moved successfully to '%s'.\n", args[1], args[2]);
    }
    else
    {
        perror("Error moving file");
    }
}
void echoppend(char **args)
{
    if (args[1] == NULL || args[2] == NULL || strcmp(args[2], ">>") != 0 || args[3] == NULL)
    {
        fprintf(stderr, "Usage: echo <text> >> <filename>\n");
        return;
    }

    FILE *file = fopen(args[3], "a"); 
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 1; i < 2; i++)
    {
        fprintf(file, "%s", args[i]);
        if (args[i + 1] != NULL && strcmp(args[i + 1], ">>") != 0)
            fprintf(file, " ");
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Text appended to file: %s\n", args[3]);
}







void echowrite(char **args)
{
   
    if (args[1] == NULL || args[2] == NULL || strcmp(args[2], ">") != 0 || args[3] == NULL)
    {
        fprintf(stderr, "Usage: echo <text> > <filename>\n");
        return;
    }

    
    FILE *file = fopen(args[3], "w");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

  
    fprintf(file, "%s\n", args[1]);

    fclose(file);
    printf("Text written to file: %s\n", args[3]);
}












void _read(char **args)
{
   
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: read <filename>\n");
        return;
    }

    FILE *file = fopen(args[1], "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
}

void wordCount(char **args)
{
    // Validate input arguments
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "Usage: wordCount <option> <filename>\nOptions: -l (lines), -w (words), -c (characters)\n");
        return;
    }

    FILE *file = fopen(args[2], "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    int lines = 0, words = 0, characters = 0;
    char ch, prev = ' ';

    while ((ch = fgetc(file)) != EOF)
    {
        characters++;
        if (ch == '\n')
            lines++;
        if ((ch == ' ' || ch == '\n' || ch == '\t') && prev != ' ' && prev != '\n' && prev != '\t')
            words++;
        prev = ch;
    }

    fclose(file);

    if (strcmp(args[1], "-l") == 0)
        printf("Lines: %d\n", lines);
    else if (strcmp(args[1], "-w") == 0)
        printf("Words: %d\n", words);
    else if (strcmp(args[1], "-c") == 0)
        printf("Characters: %d\n", characters);
    else
        fprintf(stderr, "Invalid option: %s\nOptions: -l (lines), -w (words), -c (characters)\n", args[1]);
}


void echo(char **arguments)
{
    if (arguments[1] == NULL)
    {
        printf("\n");
        return;
    }

    int redirectIndex = -1;

    for (int i = 1; arguments[i] != NULL; i++)
    {
        if (strcmp(arguments[i], ">") == 0 && arguments[i + 1] != NULL)
        {
            redirectIndex = i;
            break;
        }
    }

    if (redirectIndex != -1)
    {
        FILE *file = fopen(arguments[redirectIndex + 1], "w"); 
        if (!file)
        {
            perror("Error opening file");
            return;
        }

        for (int i = 1; i < redirectIndex; i++)
        {
            fprintf(file, "%s", arguments[i]);
            if (i + 1 < redirectIndex)
                fprintf(file, " ");
        }
        fprintf(file, "\n");

        fclose(file);
        printf("Text written to file: %s\n", arguments[redirectIndex + 1]);
    }
    else 
    {
        for (int i = 1; arguments[i] != NULL; i++)
        {
            printf("%s", arguments[i]);
            if (arguments[i + 1] != NULL)
                printf(" ");
        }
        printf("\n");
    }
}


void cd(char **arguments)
{
    if (arguments[1] == NULL)
    {
        fprintf(stderr, "-myShell: cd: missing argument\n");
        return;
    }

    char path[256] = "";
    int i = 1;

    while (arguments[i] != NULL)
    {
        strcat(path, arguments[i]);
        if (arguments[i + 1] != NULL)
            strcat(path, " ");  
        i++;
    }

    printf("[DEBUG] Changing directory to: %s\n", path);

    if (chdir(path) != 0)
        perror("-myShell: cd");
}



void cp(char **arguments)
{
    // Validate input arguments
    if (arguments[1] == NULL || arguments[2] == NULL)
    {
        fprintf(stderr, "Usage: cp <source_file> <destination_file>\n");
        return;
    }

    // Open source file
    FILE *source = fopen(arguments[1], "rb");
    if (!source)
    {
        fprintf(stderr, "Error opening source file: %s\n", arguments[1]);
        perror("Error");
        return;
    }

    // Open destination file
    FILE *destination = fopen(arguments[2], "wb");
    if (!destination)
    {
        fprintf(stderr, "Error opening destination file: %s\n", arguments[2]);
        perror("Error");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes;

    // Copy file contents
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0)
    {
        if (fwrite(buffer, 1, bytes, destination) != bytes)
        {
            fprintf(stderr, "Error writing to destination file: %s\n", arguments[2]);
            perror("Error");
            fclose(source);
            fclose(destination);
            return;
        }
    }

    fclose(source);
    fclose(destination);
    printf("File copied successfully: %s -> %s\n", arguments[1], arguments[2]);
}

void get_dir()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // Open current directory
    if (!dir)
    {
        perror("Error opening directory");
        return;
    }

    int count = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\t", entry->d_name);
        count++;
        if (count % 5 == 0) // Print 5 per row for readability
            printf("\n");
    }
    printf("\n");

    closedir(dir);
}

void delete(char **arguments)
{
    // Validate input arguments
    if (arguments[1] == NULL)
    {
        fprintf(stderr, "Usage: delete <filename>\n");
        return;
    }

    // Attempt to remove the file
    if (remove(arguments[1]) == 0)
    {
        printf("File '%s' deleted successfully.\n", arguments[1]);
    }
    else
    {
        perror("Error deleting file");
    }
}

