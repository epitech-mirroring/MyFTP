/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <printf.h>
#include "ftp_server.h"

int main(int argc, char **argv)
{
    ftp_server_t *server;

    if (argc != 3 ||
        (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport is the port number on which the server"
            " socket listens\n");
        printf("\tpath is the path to the home directory for"
            " the Anonymous user\n");
        return 0;
    }
    server = ftp_server_create(atoi(argv[1]), argv[2]);
    ftp_server_start(server);
    ftp_server_destroy(server);
    return 0;
}
