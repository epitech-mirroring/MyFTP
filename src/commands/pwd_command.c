/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdio.h>
#include "commands/pwd_command.h"

void register_pwd_command(void)
{
    ftp_command_t *cmd = malloc(sizeof(ftp_command_t));

    cmd->name = "pwd";
    cmd->callback = &pwd_callback;
    cmd->expected_args_nb_min = 0;
    cmd->expected_args_nb_max = 0;
    cmd->help = "Print working directory.";
    cmd->needs_auth = true;
    cmd->needs_mode_selected = false;
    ftp_command_registry(true, cmd);
}

void pwd_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *msg;
    char *rpath;

    (void)server;
    (void)args;
    rpath = realpath(client->wd_path, NULL);
    asprintf(&msg, "257 \"%s\"\r\n", rpath);
    ftp_client_send(client, msg);
}
