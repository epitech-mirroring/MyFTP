/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "commands/noop_command.h"

void register_noop_command(void)
{
    ftp_command_t *cmd = malloc(sizeof(ftp_command_t));

    cmd->name = "noop";
    cmd->callback = &noop_callback;
    cmd->expected_args_nb_min = 0;
    cmd->expected_args_nb_max = 0;
    cmd->help = "Do nothing.";
    cmd->needs_auth = false;
    cmd->needs_mode_selected = false;
    ftp_command_registry(true, cmd);
}

void noop_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    (void)server;
    (void)args;
    ftp_client_send(client, "200 NOOP ok.\r\n");
}
