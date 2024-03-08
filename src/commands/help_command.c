/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "commands/help_command.h"

void register_help_command(void)
{
    ftp_command_t *help_cmd = malloc(sizeof(ftp_command_t));

    help_cmd->name = "help";
    help_cmd->expected_args_nb_min = 0;
    help_cmd->expected_args_nb_max = 1;
    help_cmd->callback = &help_callback;
    help_cmd->help = "Display the list of available commands"
        "or the help for a specific command";
    help_cmd->needs_auth = false;
    help_cmd->needs_mode_selected = false;
    ftp_command_registry(true, help_cmd);
}

static char *to_lower(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
        str[i] = (char) tolower(str[i]);
    return str;
}

void help_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    ftp_command_t ***commands = ftp_command_registry(false, NULL);

    if (args[0] == NULL) {
        ftp_client_send(client, "214-The following commands "
            "are recognized.\r\n");
        for (int i = 0; (*commands)[i] != NULL; i++)
            dprintf(client->socket, " %s\r\n", (*commands)[i]->name);
        ftp_client_send(client, "214 Help OK.\r\n");
        return;
    }
    for (int i = 0; (*commands)[i] != NULL; i++)
        if (strcmp((*commands)[i]->name, to_lower(args[0])) == 0) {
            dprintf(client->socket, "214 %s\r\n",
                (*commands)[i]->help);
            dprintf(client->socket, "214 Help OK.\r\n");
            return;
        }
    ftp_client_send(client, "504 Command not implemented "
        "for that parameter.\r\n");
}
