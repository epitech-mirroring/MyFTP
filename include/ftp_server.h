/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
typedef struct ftp_client_s ftp_client_t;
#include <stdbool.h>
#include <stdlib.h>
#include "ftp_client.h"
#include <dirent.h>

typedef struct ftp_server_s {
    int socket;
    int port;
    int binded;
    char *path;
    size_t nb_clients;
    ftp_client_t **clients;
    bool running;
    int max_socket;
    DIR *server_dir;
} ftp_server_t;

// ------------------ Constructors / Destructors ------------------
ftp_server_t *ftp_server_create(int port, char *path);
void ftp_server_destroy(ftp_server_t *server);

// ------------------ Methods ------------------
bool ftp_server_start(ftp_server_t *server);
void ftp_server_stop(ftp_server_t *server);
void ftp_server_run(ftp_server_t *server);
void ftp_server_accept_client(ftp_server_t *server);
void ftp_server_disconnect_client(ftp_server_t *server, size_t index);
size_t ftp_server_get_client_index(ftp_server_t *server, ftp_client_t *client);
