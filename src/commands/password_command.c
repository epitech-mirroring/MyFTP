/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdio.h>
#include "commands/password_command.h"

void register_password_command(void)
{
    ftp_command_t *password_command = malloc(sizeof(ftp_command_t));

    password_command->name = "pass";
    password_command->expected_args_nb_min = 1;
    password_command->expected_args_nb_max = 1;
    password_command->callback = &password_callback;
    password_command->help = "Specify password for authentication";
    password_command->needs_auth = false;
    password_command->needs_mode_selected = false;
    ftp_command_registry(true, password_command);
}

void password_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    (void)server;
    if (client->is_authenticated) {
        ftp_client_send(client, "230 User logged in, proceed.\r\n");
        return;
    }
    if (client->username == NULL || strlen(client->username) < 1) {
        ftp_client_send(client, "332 Need account for login.\r\n");
        return;
    }
    if (strcmp(client->username, "Anonymous") == 0 && strlen(args[0]) == 0) {
        ftp_client_send(client, "230 User logged in, proceed.\r\n");
        client->is_authenticated = true;
        return;
    }
    ftp_client_send(client, "530 Not logged in.\r\n");
}
