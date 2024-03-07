/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ftp_client.h"

ftp_client_t *ftp_client_init(int socket, struct sockaddr_in *csin,
    ftp_server_t *server)
{
    ftp_client_t *client = malloc(sizeof(ftp_client_t));

    client->socket = socket;
    client->ip = inet_ntoa(csin->sin_addr);
    client->port = ntohs(csin->sin_port);
    client->is_authenticated = false;
    client->username = NULL;
    client->working_dir = opendir(server->path);
    client->wd_path = strdup(server->path);
    client->mode = UNDEFINED;
    client->data_socket = -1;
    client->data_addr = (struct sockaddr_in){0};
    return client;
}

void ftp_client_destroy(ftp_client_t *client)
{
    close(client->socket);
    closedir(client->working_dir);
    free(client->wd_path);
    free(client);
}

void ftp_client_send(ftp_client_t *client, char *message)
{
    write(client->socket, message, strlen(message));
}
