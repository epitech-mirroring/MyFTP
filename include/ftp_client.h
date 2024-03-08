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
#include <netinet/in.h>
#include "ftp_server.h"

typedef enum ftp_client_mod_e {
    ACTIVE,
    PASSIVE,
    UNDEFINED
} ftp_client_mod_t;

typedef struct ftp_client_s {
    int socket;
    struct in_addr ip;
    int port;
    bool is_authenticated;
    char *username;
    DIR *working_dir;
    char *wd_path;
    int data_socket;
    struct sockaddr_in data_addr;
    ftp_client_mod_t mode;
    int client_data_port;
} ftp_client_t;

// ------------------ Constructors / Destructors ------------------
ftp_client_t *ftp_client_init(int socket, struct sockaddr_in *csin,
    ftp_server_t *server);
void ftp_client_destroy(ftp_client_t *client);

// ------------------ Methods ------------------
void ftp_client_send(ftp_client_t *client, char *message);
int ftp_client_get_data_socket(ftp_client_t *client);
