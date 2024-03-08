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
#include "commands/retrieve_command.h"
#include "commands/cwd_command.h"

void register_retrieve_command(void)
{
    ftp_command_t *retr_command = malloc(sizeof(ftp_command_t));

    retr_command->name = "retr";
    retr_command->expected_args_nb_min = 1;
    retr_command->expected_args_nb_max = 1;
    retr_command->callback = &retr_callback;
    retr_command->help = "List files in the current directory";
    retr_command->needs_auth = true;
    retr_command->needs_mode_selected = true;
    ftp_command_registry(true, retr_command);
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

static void handle_retr(ftp_client_t *client, FILE *file)
{
    int buffer[1];
    int data_socket;

    dprintf(client->socket, "150 File status okay; about"
        "to open data connection.\r\n");
    if (fork() == 0) {
        data_socket = ftp_client_get_data_socket(client);
        if (data_socket == -1) {
            dprintf(client->socket, "425 Can not open data connection.\r\n");
            exit(0);
        }
        while (fread(buffer, 1, 1, file) > 0) {
            write(data_socket, buffer, 1);
        }
        close(data_socket);
        exit(0);
    }
    fclose(file);
    ftp_client_send(client, "226 File succesfly sent\r\n");
}

void retr_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *path = concat_path(client->wd_path, args[0]);
    FILE *file;

    if (!is_subdir(server->path, path)) {
        ftp_client_send(client, "550 Permission denied.\r\n");
        free(path);
        return;
    }
    file = fopen(path, "r");
    if (file == NULL) {
        dprintf(client->socket, "550 Can't read file on host.\r\n");
        free(path);
        return;
    }
    handle_retr(client, file);
    free(path);
}
