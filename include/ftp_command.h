/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "ftp_server.h"
#include "ftp_client.h"

typedef void (*ftp_command_callback_t)(ftp_server_t *server,
    ftp_client_t *client, char **args);

typedef struct ftp_prepared_command_s {
    char *name;
    char **args;
    size_t args_nb;
} ftp_prepared_command_t;

typedef struct ftp_command_s {
    char *name;
    ftp_command_callback_t callback;
    size_t expected_args_nb_min;
    size_t expected_args_nb_max;
    char *help;
    bool needs_auth;
    bool needs_mode_selected;
} ftp_command_t;

// ------------------ Methods ------------------
void ftp_command_execute(ftp_server_t *server, ftp_client_t *client,
    char *command);
ftp_command_t ***ftp_command_registry(bool write, void *data);
ftp_prepared_command_t *ftp_command_prepare(char *command);
void ftp_command_destroy_registry(void);
void ftp_command_destroy_prepared(ftp_prepared_command_t *prepared_command);
ftp_prepared_command_t *ftp_command_sanitise(ftp_prepared_command_t *prepared);
