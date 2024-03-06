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

ftp_client_t *ftp_client_init(int socket, struct sockaddr_in *csin)
{
    ftp_client_t *client = malloc(sizeof(ftp_client_t));

    client->socket = socket;
    client->ip = inet_ntoa(csin->sin_addr);
    client->port = ntohs(csin->sin_port);
    return client;
}

void ftp_client_destroy(ftp_client_t *client)
{
    close(client->socket);
    free(client);
}

void ftp_client_send(ftp_client_t *client, char *message)
{
    write(client->socket, message, strlen(message));
}
