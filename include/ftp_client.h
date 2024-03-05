/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

typedef struct ftp_client_s {
    int socket;
    char *ip;
    int port;
} ftp_client_t;

ftp_client_t ftp_client_init(int socket, struct sockaddr_in *csin);
