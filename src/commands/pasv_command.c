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
#include <stdbool.h>
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

static bool create_data_channel(ftp_client_t *client)
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
        sizeof(client->data_addr)) == -1) {
        return false;
    }
    if (listen(client->data_socket, 1) == -1) {
        return false;
    }
    return true;
}

void pasv_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    socklen_t len;
    struct sockaddr_in sin = {0};
    socklen_t len2 = sizeof(sin);
    in_addr_t ip;

    if (!create_data_channel(client)) {
        ftp_client_send(client, "425 Can not open data connection.\r\n");
        return;
    }
    client->mode = PASSIVE;
    len = sizeof(client->data_addr);
    getsockname(client->data_socket,
        (struct sockaddr *)&client->data_addr, &len);
    client->client_data_port = ntohs(client->data_addr.sin_port);
    getsockname(client->socket, (struct sockaddr *)&sin, &len2);
    ip = ntohl(sin.sin_addr.s_addr);
    dprintf(client->socket, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)."
        "\r\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF,
        (ip >> 8) & 0xFF, ip & 0xFF, (client->client_data_port >> 8) & 0xFF,
        client->client_data_port & 0xFF);
}
