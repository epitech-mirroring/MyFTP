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
#include "commands/store_command.h"

void register_store_command(void)
{
    ftp_command_t *store_command = malloc(sizeof(ftp_command_t));

    store_command->name = "stor";
    store_command->expected_args_nb_min = 1;
    store_command->expected_args_nb_max = 1;
    store_command->callback = &store_callback;
    store_command->help = "List files in the current directory";
    store_command->needs_auth = true;
    store_command->needs_mode_selected = true;
    ftp_command_registry(true, store_command);
}

static char *concat_path(char *path, char *string)
{
    char *new_path = malloc((strlen(path) +
        strlen(string) + 2) * sizeof(char));

    strcpy(new_path, path);
    strcat(new_path, "/");
    strcat(new_path, string);
    return new_path;
}

static void handle_store(ftp_client_t *client, FILE *target)
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
        while (read(data_socket, buffer, 1) > 0) {
            fwrite(buffer, 1, 1, target);
        }
        close(data_socket);
        exit(0);
    }
    fclose(target);
    ftp_client_send(client, "226 File transferred successfully.\r\n");
}

void store_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *path = concat_path(client->wd_path, args[0]);
    char *rp;
    FILE *target;

    target = fopen(path, "w");
    if (target == NULL) {
        dprintf(client->socket, "550 Can't create file on host.\r\n");
        free(path);
        return;
    }
    handle_store(client, target);
    free(path);
}
