/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <arpa/inet.h>
#include "ftp_client.h"

ftp_client_t ftp_client_init(int socket, struct sockaddr_in *csin)
{
    return (ftp_client_t) {
            .socket = socket,
            .ip = inet_ntoa(csin->sin_addr),
            .port = ntohs(csin->sin_port)
    };
}
