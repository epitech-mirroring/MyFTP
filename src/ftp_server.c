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
#include <printf.h>
#include "ftp_server.h"
#include "ftp_command.h"

ftp_server_t *ftp_server_create(int port, char *path)
{
    ftp_server_t *server = malloc(sizeof(ftp_server_t));

    if (!server) {
        perror("Can not allocate memory for server");
        return NULL;
    }
    server->port = port;
    server->path = path;
    server->nb_clients = 0;
    server->clients = NULL;
    return server;
}

static void ftp_server_update_max_socket(ftp_server_t *server)
{
    for (size_t i = 0; i < server->nb_clients; i++) {
        if (server->clients[i]->socket > server->max_socket)
            server->max_socket = server->clients[i]->socket;
    }
}

void ftp_server_destroy(ftp_server_t *server)
{
    for (size_t i = 0; i < server->nb_clients; i++) {
        ftp_client_destroy(server->clients[i]);
    }
    free(server->clients);
    close(server->socket);
    ftp_command_destroy_registry();
}

void ftp_server_stop(ftp_server_t *server)
{
    server->running = false;
    close(server->socket);
}

bool ftp_server_start(ftp_server_t *server)
{
    struct sockaddr_in sin = {
            .sin_family = AF_INET,
            .sin_port = htons(server->port),
            .sin_addr.s_addr = INADDR_ANY
    };

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &(int){1},
            sizeof(int)) < 0) {
        return false;
    }
    server->binded = bind(server->socket, (struct sockaddr*)&sin, sizeof(sin));
    if (server->binded == -1) {
        return false;
    }
    listen(server->socket, 42);
    server->max_socket = server->socket;
    ftp_server_run(server);
    ftp_server_stop(server);
    return true;
}

void ftp_server_disconnect_client(ftp_server_t *server, size_t index)
{
    ftp_client_destroy(server->clients[index]);
    for (size_t i = index; i < server->nb_clients - 1; i++) {
        server->clients[i] = server->clients[i + 1];
    }
    server->nb_clients--;
    if (server->nb_clients == 0) {
        free(server->clients);
        server->clients = NULL;
    } else {
        server->clients = realloc(server->clients,
            sizeof(ftp_client_t *) * server->nb_clients);
        if (server->clients == NULL) {
            perror("Can not reallocate memory for clients");
            return;
        }
    }
    ftp_server_update_max_socket(server);
}
