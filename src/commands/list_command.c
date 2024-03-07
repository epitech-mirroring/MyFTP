/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands/list_command.h"

void register_list_command(void)
{
    ftp_command_t *list_command = malloc(sizeof(ftp_command_t));

    list_command->name = "list";
    list_command->expected_args_nb_min = 0;
    list_command->expected_args_nb_max = 1;
    list_command->callback = &list_callback;
    list_command->help = "List files in the current directory";
    list_command->needs_auth = true;
    list_command->needs_mode_selected = true;
    ftp_command_registry(true, list_command);
}

static char *concat_path(char *path, char *string)
{
    char *new_path = malloc((strlen(path) +
        strlen(string) + 2) * sizeof(char));
    char *re;

    strcpy(new_path, path);
    strcat(new_path, "/");
    strcat(new_path, string);
    re = realpath(new_path, NULL);
    free(new_path);
    return re;
}

static void handle_ls(ftp_client_t *client, FILE *command_out)
{
    int buffer[1];
    int data_socket;

    dprintf(client->socket, "150 Here comes the directory listing.\r\n");
    if (fork() == 0) {
        data_socket = ftp_client_get_data_socket(client);
        if (data_socket == -1) {
            dprintf(client->socket, "425 Can not open data connection.\r\n");
            exit(0);
        }
        while (fread(buffer, 1, 1, command_out) > 0) {
            write(data_socket, buffer, 1);
        }
        close(data_socket);
        exit(0);
    }
    pclose(command_out);
    ftp_client_send(client, "226 Directory send OK.\r\n");
}

void list_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *path = args[0] != NULL ? concat_path(client->wd_path, args[0]) :
        realpath(client->wd_path, NULL);
    char *command;
    FILE *ret;

    (void)server;
    command = malloc((strlen("ls -l ") + strlen(path) + 1) * sizeof(char));
    strcpy(command, "ls -l ");
    strcat(command, path);
    ret = popen(command, "r");
    if (ret == NULL) {
        dprintf(client->socket, "550 Failed to list directory.\r\n");
        free(path);
        free(command);
        return;
    }
    handle_ls(client, ret);
    free(path);
    free(command);
}
