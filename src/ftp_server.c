/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ftp_server.h"

ftp_server_t *ftp_server_create(int port, char *path)
{
    ftp_server_t *server = malloc(sizeof(ftp_server_t));

    server->port = port;
    server->path = path;
    server->nb_clients = 0;
    server->clients = NULL;
    return server;
}

void ftp_server_run(ftp_server_t *server)
{
    struct sockaddr_in sin = {
        .sin_family = AF_INET,
        .sin_port = htons(server->port),
        .sin_addr.s_addr = INADDR_ANY
    };

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    server->binded = bind(server->socket, (struct sockaddr*)&sin, sizeof(sin));
    if (server->binded == -1)
        return;
    listen(server->socket, 42);
    server->running = true;
    while (server->running) {
        ftp_server_manage_client(server);
    }
}

void ftp_server_manage_client(ftp_server_t *server)
{
    struct sockaddr_in csin;
    socklen_t size = sizeof(csin);
    int client_socket = accept(server->socket, (struct sockaddr*)&csin, &size);

    if (client_socket == -1)
        return;
    server->nb_clients++;
    server->clients = realloc(server->clients,
                                sizeof(ftp_client_t) * server->nb_clients);
    if (server->clients == NULL)
        return;
    server->clients[server->nb_clients - 1] =
                                        ftp_client_init(client_socket, &csin);
}
