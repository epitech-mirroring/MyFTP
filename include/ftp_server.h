/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "ftp_client.h"

typedef struct ftp_server_s {
    int socket;
    int port;
    int binded;
    char *path;
    size_t nb_clients;
    ftp_client_t *clients;
    bool running;
} ftp_server_t;

ftp_server_t *ftp_server_create(int port, char *path);
void ftp_server_run(ftp_server_t *server);
void ftp_server_manage_client(ftp_server_t *server);
