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
#include <stdio.h>
#include "ftp_client.h"

ftp_client_t *ftp_client_init(int socket, struct sockaddr_in *csin,
    ftp_server_t *server)
{
    ftp_client_t *client = malloc(sizeof(ftp_client_t));

    client->socket = socket;
    client->ip = csin->sin_addr;
    client->port = ntohs(csin->sin_port);
    client->is_authenticated = false;
    client->username = NULL;
    client->working_dir = opendir(server->path);
    client->wd_path = strdup(server->path);
    client->mode = UNDEFINED;
    client->data_socket = -1;
    client->data_addr = (struct sockaddr_in){0};
    client->client_data_port = 0;
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

int ftp_client_get_data_socket(ftp_client_t *client)
{
    struct sockaddr_in csin;
    socklen_t size = sizeof(csin);
    int s;
    int r;

    if (client->mode == PASSIVE) {
        return accept(client->data_socket, (struct sockaddr*)&csin, &size);
    } else if (client->mode == ACTIVE) {
        s = socket(AF_INET, SOCK_STREAM, 0);
        csin.sin_family = AF_INET;
        csin.sin_addr.s_addr = client->ip.s_addr;
        csin.sin_port = htons(client->client_data_port);
        r = connect(s, (struct sockaddr*)&csin, size);
        return r == -1 ? -1 : s;
    }
    return -1;
}
