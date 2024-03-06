/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
typedef struct ftp_server_s ftp_server_t;
#include <stdbool.h>
#include <dirent.h>
#include "ftp_server.h"

typedef struct ftp_client_s {
    int socket;
    char *ip;
    int port;
    bool is_authenticated;
    char *username;
    DIR *working_dir;
    char *wd_path;
} ftp_client_t;

// ------------------ Constructors / Destructors ------------------
ftp_client_t *ftp_client_init(int socket, struct sockaddr_in *csin,
    ftp_server_t *server);
void ftp_client_destroy(ftp_client_t *client);

// ------------------ Methods ------------------
void ftp_client_send(ftp_client_t *client, char *message);
