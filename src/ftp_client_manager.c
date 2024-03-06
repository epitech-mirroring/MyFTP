/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <unistd.h>
#include <printf.h>
#include "ftp_client_manager.h"
#include "ftp_command.h"

void ftp_client_manager_manage_clients(ftp_server_t *server, fd_set *readfds)
{
    for (size_t i = 0; i < server->nb_clients; i++) {
        if (FD_ISSET(server->clients[i]->socket, readfds)) {
            ftp_client_manager_handle_client(server, i);
        }
    }
}

void ftp_client_manager_handle_client(ftp_server_t *server, size_t index)
{
    char buffer[1024] = {0};
    int valread = read(server->clients[index]->socket, buffer, 1024);

    if (valread == 0) {
        ftp_server_disconnect_client(server, index);
    } else {
        ftp_command_execute(server, server->clients[index],
            buffer);
    }
}
