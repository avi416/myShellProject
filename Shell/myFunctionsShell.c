#include "myFunctionsShell.h"

char *getInputFromUser()
{

    char ch;
    int len = 0;
    char *input = (char *)malloc(sizeof(char) * (len + 1));
    *input = '\0';
    while ((ch = getchar()) != '\n')
    {
        *(input + len) = ch;
        input = (char *)realloc(input, (++len + 1));
    }
    *(input + len) = '\0';

    return input;
}

char **splitArguments(char *input)
{

    char **arguments = (char **)malloc(sizeof(char *) * 7);
    arguments[0] = input;
    arguments[1] = input + 4;
    arguments[2] = input + 7;

    return NULL;
}

void getLocation()
{
    char location[256];
    char *user = getenv("USER"); // Get the username
    char host[256];
    gethostname(host, sizeof(host)); // Get the hostname

    if (getcwd(location, sizeof(location)) == NULL)
    {
        puts("Error");
        return;
    }

    // Print location with colors
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", user, host, location);
}

void logout(char *input)
{
    char *trimmed = strtok(input, " \t"); // Trim leading spaces
    if (trimmed != NULL && strcmp(trimmed, "exit") == 0)
    {
        puts("Exiting myShell...");
        free(input);
        exit(EXIT_SUCCESS);
    }
}


void systemCall(char **arguments)
{
    puts("systemCall");
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork err");
        return;
    }

    if (pid == 0)
    {

        if (execvp(arguments[0], arguments) == -1)
        {
            exit(EXIT_FAILURE);
        }
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


void move(char **args) {}
void echoppend(char **args) {}
void echowrite(char **args) {}
void _read(char **args) {}
void wordCount(char **args) {}

void echo(char **arguments)
{
    while (*(++arguments))
        printf("%s ", *arguments);

    puts("");
}
void cd(char **arguments)
{
    char path[256] = "";
    int i = 1;

    // Concatenate all arguments into a single path string
    while (arguments[i] != NULL)
    {
        strcat(path, arguments[i]);
        if (arguments[i + 1] != NULL)
            strcat(path, " "); // Preserve spaces between words
        i++;
    }

    // Change directory and handle errors
    if (chdir(path) != 0)
        printf("-myShell: cd: %s: No such file or directory\n", path);
}

void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("error");
        return;
    }

    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("error");
        fclose(src);
        return;
    }
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, des);

    fclose(src);
    fclose(des);
}
void get_dir()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) == NULL)
    {
        perror("");
        return;
    }
    while ((ent = readdir(dir)) != NULL)
        printf("%s ", ent->d_name);
    puts("");
}
void delete(char **arguments)
{
    if (unlink(arguments[1]) != 0)
        printf("-myShell: delete: %s: No such file or directory\n", arguments[1]);
}
