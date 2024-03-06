/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "ftp_server.h"
#include "ftp_client_manager.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

void ftp_server_run(ftp_server_t *server)
{
    fd_set readfds = {0};
    struct timeval timeout = {0, 1000};

    server->running = true;
    while (server->running) {
        FD_ZERO(&readfds);
        FD_SET(server->socket, &readfds);
        for (size_t i = 0; i < server->nb_clients; i++) {
            FD_SET(server->clients[i]->socket, &readfds);
        }
        if (select(server->max_socket + 1, &readfds,
            NULL, NULL, &timeout) == -1) {
            perror("Select failed");
            return;
        }
        if (FD_ISSET(server->socket, &readfds)) {
            ftp_server_accept_client(server);
        }
        ftp_client_manager_manage_clients(server, &readfds);
    }
}

void ftp_server_accept_client(ftp_server_t *server)
{
    struct sockaddr_in csin;
    socklen_t size = sizeof(csin);
    int client_socket = accept(server->socket, (struct sockaddr*)&csin, &size);

    if (client_socket == -1)
        return;
    server->nb_clients++;
    server->clients = realloc(server->clients,
        sizeof(ftp_client_t *) * server->nb_clients);
    if (server->clients == NULL)
        return;
    server->clients[server->nb_clients - 1] =
            ftp_client_init(client_socket, &csin);
    write(client_socket, "220 Service ready for new user.\r\n", 33);
    if (client_socket > server->max_socket)
        server->max_socket = client_socket;
}

size_t ftp_server_get_client_index(ftp_server_t *server, ftp_client_t *client)
{
    for (size_t i = 0; i < server->nb_clients; i++) {
        if (server->clients[i] == client)
            return i;
    }
    return -1;
}
