/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include "commands/user_command.h"

void register_user_command(void)
{
    ftp_command_t *user_command = malloc(sizeof(ftp_command_t));
    user_command->name = "user";
    user_command->expected_args_nb = 1;
    user_command->callback = &user_callback;
    user_command->help = "Specify user for authentication";
    ftp_command_registry(true, user_command);
}

void user_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    (void)server;
    if (client->is_authenticated) {
        ftp_client_send(client, "230 User logged in, proceed.\r\n");
        return;
    }
    if (strlen(args[0]) < 1 || strlen(args[0]) > 32) {
        ftp_client_send(client, "501 Invalid username.\r\n");
        return;
    }
    client->username = strdup(args[0]);
    ftp_client_send(client, "331 User name okay, need password.\r\n");
}
