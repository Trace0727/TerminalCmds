#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARG_LENGTH 100

// Handler for Ctrl+C
void handle_sigint(int sig) {
    printf("\nprogram exited\n");
    exit(0);
}

void show_help() {
    printf("\nSupported commands:\n");
    printf("  cd <directory>       - Change to the specified directory\n");
    printf("  dir                  - List contents of the current directory\n");
    printf("  type <file>          - Show the type of the file\n");
    printf("  del <file>           - Delete the specified file\n");
    printf("  ren <old> <new>      - Rename a file\n");
    printf("  copy <src> <dest>    - Copy a file\n");
}

void execute_command(char *command, char *arg1, char *arg2) {
    if (strcmp(command, "cd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("\nCurrent working directory: %s\n", cwd);
        }
        if (arg1[0] != '\0') {
            printf("UNIX command: cd\n");
            if (chdir(arg1) == 0) {
                printf("Changed directory to %s\n", arg1);
            } else {
                perror("Failed to change directory");
            }
        } else {
            printf("Missing arguments for cd command.\n");
        }
    } else if (strcmp(command, "dir") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("\nCurrent working directory: %s\n", cwd);
        }
        printf("UNIX command: ls\n");
        system("ls");
    } else if (strcmp(command, "type") == 0) {
        if (arg1[0] != '\0') {
            printf("UNIX command: file\n");
            char sys_cmd[200];
            snprintf(sys_cmd, sizeof(sys_cmd), "file \"%s\"", arg1);
            system(sys_cmd);
        } else {
            printf("Missing filename argument for type command.\n");
        }
    } else if (strcmp(command, "ren") == 0) {
        if (arg1[0] != '\0' && arg2[0] != '\0') {
            printf("UNIX command: mv\n");
            char sys_cmd[200];
            snprintf(sys_cmd, sizeof(sys_cmd), "mv \"%s\" \"%s\"", arg1, arg2);
            int result = system(sys_cmd);
            if (result == 0) {
                printf("Renamed file from \"%s\" to \"%s\"\n", arg1, arg2);
            } else {
                printf("Failed to rename file from \"%s\" to \"%s\"\n", arg1, arg2);
            }
        } else {
            printf("Missing arguments for ren command.\n");
        }
    } else if (strcmp(command, "del") == 0) {
        if (arg1[0] != '\0') {
            printf("UNIX command: rm\n");
            if (remove(arg1) == 0) {
                printf("Deleted file \"%s\"\n", arg1);
            } else {
                perror("Failed to delete file");
            }
        } else {
            printf("Missing filename argument for del command.\n");
        }
    } else if (strcmp(command, "copy") == 0) {
        if (arg1[0] != '\0' && arg2[0] != '\0') {
            printf("UNIX command: cp\n");
            char sys_cmd[200];
            snprintf(sys_cmd, sizeof(sys_cmd), "cp \"%s\" \"%s\"", arg1, arg2);
            int result = system(sys_cmd);
            if (result == 0) {
                printf("Copied file \"%s\" to \"%s\"\n", arg1, arg2);
            } else {
                printf("Failed to copy file \"%s\" to \"%s\"\n", arg1, arg2);
            }
        } else {
            printf("Missing arguments for copy command.\n");
        }
    } else if (strcmp(command, "help") == 0) {
        show_help();
    } else {
        printf("Invalid command. Type 'help' to see available commands.\n");
    }
}

int main() {
    signal(SIGINT, handle_sigint);  // Ctrl+C support

    char command[MAX_COMMAND_LENGTH];
    char arg1[MAX_ARG_LENGTH];
    char arg2[MAX_ARG_LENGTH];
    char buffer[MAX_COMMAND_LENGTH + 2];

    while (1) {
        arg1[0] = '\0';
        arg2[0] = '\0';

        printf("\n\nType a DOS command (cd, dir, type, del, ren, copy):\n");
        printf("Extra options: Type 'help' to see command descriptions, 'exit' to stop program in IDE, or press Ctrl+C to exit in terminal:\n");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\nprogram exited\n");
                break;
            } else {
                perror("fgets error");
                exit(EXIT_FAILURE);
            }
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char *token = strtok(buffer, " ");
        if (token == NULL) {
            printf("Invalid input. Please provide a command.\n");
            continue;
        }
        strcpy(command, token);

        // Support typed exit
        if (strcmp(command, "exit") == 0) {
            printf("\nprogram exited\n");
            break;
        }

        token = strtok(NULL, " ");
        if (token != NULL) {
            strcpy(arg1, token);
            token = strtok(NULL, " ");
            if (token != NULL) {
                if (strcmp(command, "del") == 0 || strcmp(command, "type") == 0) {
                    printf("Command '%s' only accepts one argument (file name).\n", command);
                    continue;
                } else {
                    strcpy(arg2, token);
                }
            } else {
                if (strcmp(command, "copy") == 0 || strcmp(command, "ren") == 0) {
                    printf("Command '%s' requires two arguments.\n", command);
                    continue;
                }
            }
        }

        execute_command(command, arg1, arg2);
    }

    return 0;
}
