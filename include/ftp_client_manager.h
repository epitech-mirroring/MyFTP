/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <sys/select.h>
#include "ftp_server.h"


// ------------------ Methods ------------------
void ftp_client_manager_handle_client(ftp_server_t *server,
    size_t index);
void ftp_client_manager_manage_clients(ftp_server_t *server,
    fd_set *readfds);
