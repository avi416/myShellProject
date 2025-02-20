#include "myShell.h"
#include "myFunctionsShell.h"

int main(void)
{
    welcome();

    while (1)
    {
        getLocation();

        char *input = getInputFromUser();
        if (!input) 
            continue; 

        if (strncmp(input, "exit", 4) == 0)
        {
            free(input);
            break;
        }

        char **arguments = splitArguments(input);
        if (!arguments || !arguments[0])
        {
            free(input);
            if (arguments) free(arguments);
            continue; 
        }

       
        int pipeIndex = -1;
        for (int i = 0; arguments[i] != NULL; i++)
        {
            if (strcmp(arguments[i], "|") == 0)
            {
                pipeIndex = i;
                break;
            }
        }

        if (pipeIndex != -1)
        {
          
            arguments[pipeIndex] = NULL;
            mypipe(arguments, &arguments[pipeIndex + 1]);
        }
        else
        {
            
            if (strcmp(arguments[0], "cd") == 0)
            {
                cd(arguments);
            }
            else if (strcmp(arguments[0], "echo") == 0)
            {
                int appendIndex = -1;
                int writeIndex  = -1;
                for (int i = 1; arguments[i] != NULL; i++)
                {
                    if (strcmp(arguments[i], ">>") == 0)
                        appendIndex = i;
                    else if (strcmp(arguments[i], ">") == 0)
                        writeIndex = i;
                }

                if (appendIndex != -1)
                    echoppend(arguments);
                else if (writeIndex != -1)
                    echowrite(arguments);
                else
                    echo(arguments);
            }
            else if (strcmp(arguments[0], "cp") == 0)
            {
                cp(arguments);
            }
            else if (strcmp(arguments[0], "move") == 0)
            {
                move(arguments);
            }
            else if (strcmp(arguments[0], "delete") == 0)
            {
                delete(arguments);
            }
            else if (strcmp(arguments[0], "dir") == 0)
            {
                get_dir();
            }
            else
            {
                systemCall(arguments);
            }
        }

        for (int i = 0; arguments[i] != NULL; i++)
            free(arguments[i]);
        free(arguments);
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
    printf("               /   \"      .d$$$P' |\\^\"l   \n");
    printf("             .'           `T$P^\"\"\"\"\"  :\n");
    printf("         ._.'      _.'                ;\n");
    printf("      `-.-\".-'-' ._.       _.-\"    .-\"   \033[1;32mAvi Mahari: The Legend\033[1;33m\n");
    printf("    `.-\" _____  ._              .-\"\n");
    printf("   -(.g$$$$$$$b.              .'      \n");
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
