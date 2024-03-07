/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include "commands/pasv_command.h"

void register_pasv_command(void)
{
    ftp_command_t *pasv_command = malloc(sizeof(ftp_command_t));

    pasv_command->name = "pasv";
    pasv_command->expected_args_nb_min = 0;
    pasv_command->expected_args_nb_max = 0;
    pasv_command->callback = &pasv_callback;
    pasv_command->help = "Enable passive mode for data transfer";
    pasv_command->needs_auth = true;
    pasv_command->needs_mode_selected = false;
    ftp_command_registry(true, pasv_command);
}

static int create_data_channel(ftp_client_t *client)
{
    if (client->data_socket != -1) {
        close(client->data_socket);
        client->data_socket = -1;
    }
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_addr.s_addr = INADDR_ANY;
    client->data_addr.sin_port = htons(0);
    if (bind(client->data_socket, (struct sockaddr *)&client->data_addr,
        sizeof(client->data_addr)) < 0) {
        perror("Can not bind data socket");
        close(client->data_socket);
        return -1;
    }
    listen(client->data_socket, 1);
    return 0;
}

void pasv_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    (void)args;
    (void)server;
    if (create_data_channel(client) == -1) {
        ftp_client_send(client, "425 Can not open data connection.\r\n");
        return;
    }
    client->mode = PASSIVE;
    dprintf(client->socket, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)."
        "\r\n",
        (client->data_addr.sin_addr.s_addr & 0xFF),
        (client->data_addr.sin_addr.s_addr & 0xFF00) >> 8,
        (client->data_addr.sin_addr.s_addr & 0xFF0000) >> 16,
        (client->data_addr.sin_addr.s_addr & 0xFF000000) >> 24,
        (client->data_addr.sin_port & 0xFF),
        (client->data_addr.sin_port & 0xFF00) >> 8);
}
