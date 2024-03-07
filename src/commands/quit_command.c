/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "commands/quit_command.h"

void register_quit_command(void)
{
    ftp_command_t *quit_command = malloc(sizeof(ftp_command_t));

    quit_command->name = "quit";
    quit_command->expected_args_nb_min = 0;
    quit_command->expected_args_nb_max = 0;
    quit_command->callback = &quit_callback;
    quit_command->help = "Close the connection to the server";
    quit_command->needs_auth = false;
    quit_command->needs_mode_selected = false;
    ftp_command_registry(true, quit_command);
}

void quit_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    (void)args;
    ftp_client_send(client, "221 Service closing control connection.\r\n");
    ftp_server_disconnect_client(server,
        ftp_server_get_client_index(server, client));
}
