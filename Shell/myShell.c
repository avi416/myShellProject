#include "myShell.h"
#include "myFunctionsShell.h"

int main(int argc, char const *argv[])
{
    welcome();
    while (1)
    {
        int isPipe = 2;
        int isEchoWrith = 0;
        int isEchoPpend = 0;

        getLocation();

        char *input = getInputFromUser();
        puts(input);
        
        if (strncmp(input, "exit", 4) == 0)
        {
             puts("Exit");
             free(input);  
             exit(0);
        }

        char **arguments = splitArguments(input);

        if (strcmp(arguments[0], "cd") == 0)
        {
              cd(arguments);
               continue;
        }
        else if (strncmp(input, "echo",4) == 0)
        {
            if (isEchoWrith)
                echowrite(arguments);
            else if (isEchoPpend)
                echoppend(arguments);
            else
                echo(arguments);
        }
        else if (strcmp(input, "cp") == 0)
        {
            cp(arguments);
        }
        else if (strcmp(input, "delete") == 0)
        {
            delete(arguments);
        }
        else if (strcmp(input, "dir") == 0)
        {
            get_dir();
        }
        else if (isPipe)
        {
            mypipe(arguments, arguments + isPipe + 1);
        }
        else if (strcmp(arguments[0], "clean") == 0)
        {
            int status = system("make clean");
            if (status == -1)
            {
                perror("Error running make clean");
            }
            else
            {
                printf("Temporary files removed.\n");
            }
        }
        else
        {
            systemCall(arguments);
            wait(NULL);
        }

        free(input);
    }

    return 0;
}

void welcome()
{
    printf("\033[1;33m"); 
    printf("                              __\n");
    printf("                            .d$$b         \033[1;34mAvi Mahari\033[1;33m\n");
    printf("                          .' TO$;\\       \033[1;32mAvi Mahari's Shell\033[1;33m\n");
    printf("                         /  : TP._;      --------------------------\n");
    printf("                        / _.;  :Tb|      \033[1;32mCustomized Terminal\033[1;33m\n");
    printf("                       /   /   ;j$j      \033[1;36mAvi Mahari Power\033[1;33m\n");
    printf("                   _.-\"       d$$$$      --------------------------\n");
    printf("                 .' ..       d$$$$;      \033[1;35mDesigned by Avi Mahari\033[1;33m\n");
    printf("                /  /P'      d$$$$P. |\n");
    printf("               /   \"      .d$$$P' |\\^\"l   \033[1;34mCode like a lion! - Avi Mahari\033[1;33m\n");
    printf("             .'           `T$P^\"\"\"\"\"  :\n");
    printf("         ._.'      _.'                ;\n");
    printf("      `-.-\".-'-' ._.       _.-\"    .-\"   \033[1;32mAvi Mahari: The Legend\033[1;33m\n");
    printf("    `.-\" _____  ._              .-\"\n");
    printf("   -(.g$$$$$$$b.              .'      \033[1;36mType 'help' for info - Avi Mahari\033[1;33m\n");
    printf("     \"\"^^T$$$P^)            .(:\n");
    printf("       _/  -\"  /.'         /:/;\n");
    printf("    ._.'-'`-'  \")/         /;/;\n");
    printf(" `-.-\"..--\"\"   \" /         /  ;\n");
    printf(".-\" ..--\"\"        -'          :\n");
    printf("..--\"\"--.-\"         (\\      .-(\\\n");
    printf("  ..--\"\"              `-\\(\\/;\n");
    printf("    _.                      :\n");
    printf("                            ;`-\n");
    printf("                           :\\\n");
    printf("                           ;\n");
    printf("\033[0m"); 
}
