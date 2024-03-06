/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdio.h>
#include "commands/delete_command.h"
#include "commands/cwd_command.h"

void register_delete_command(void)
{
    ftp_command_t *delete_command = malloc(sizeof(ftp_command_t));

    delete_command->name = "dele";
    delete_command->expected_args_nb = 1;
    delete_command->callback = &delete_callback;
    delete_command->help = "Delete a file";
    delete_command->needs_auth = true;
    ftp_command_registry(true, delete_command);
}

void delete_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *full_path = NULL;

    (void)server;
    full_path = malloc(strlen(client->wd_path) + strlen(args[0]) + 2);
    strcpy(full_path, client->wd_path);
    strcat(full_path, "/");
    strcat(full_path, args[0]);
    if (is_subdir(server->path, full_path) == false) {
        ftp_client_send(client, "550 Permission denied.\r\n");
        free(full_path);
        return;
    }
    if (remove(full_path) == 0)
        ftp_client_send(client,
            "250 Requested file action okay, completed.\r\n");
    else
        ftp_client_send(client, "550 Requested action not taken.\r\n");
}
