/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "ftp_server.h"

int main(int argc, char **argv)
{
    ftp_server_t *server = ftp_server_create(4242, "./");

    (void)argc;
    (void)argv;
    ftp_server_run(server);
    return 0;
}
