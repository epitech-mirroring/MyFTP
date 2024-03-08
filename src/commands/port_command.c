/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "commands/port_command.h"
#include "utils/my.h"

void register_port_command(void)
{
    ftp_command_t *port_command = malloc(sizeof(ftp_command_t));

    port_command->name = "port";
    port_command->expected_args_nb_min = 1;
    port_command->expected_args_nb_max = 1;
    port_command->callback = &port_callback;
    port_command->help =
        "Specify an address and port to which the server should connect.";
    port_command->needs_auth = true;
    port_command->needs_mode_selected = false;
    ftp_command_registry(true, port_command);
}

static char *get_host(char a, char b, char c, char d)
{
    char *host = malloc(16 * sizeof(char));

    sprintf(host, "%d.%d.%d.%d", a, b, c, d);
    return host;
}

void port_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char **host = my_split(args[0], ',');

    if (client->data_socket != -1) {
        close(client->data_socket);
        client->data_socket = -1;
    }
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_port = htons(atoi(host[4]) * 256 + atoi(host[5]));
    client->data_addr.sin_addr.s_addr = inet_addr(
        get_host(atoi(host[0]), atoi(host[1]), atoi(host[2]), atoi(host[3])));
    client->mode = ACTIVE;
    client->client_data_port = atoi(host[4]) * 256 + atoi(host[5]);
    dprintf(client->socket, "200 PORT command successful.\r\n");
}
