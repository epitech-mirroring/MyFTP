/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "ftp_command.h"

void register_pasv_command(void);
void pasv_callback(ftp_server_t *server, ftp_client_t *client,
    char **args);