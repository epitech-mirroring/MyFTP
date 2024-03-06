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
#include "commands/user_command.h"
#include "commands/password_command.h"
#include "commands/quit_command.h"
#include "commands/cwd_command.h"
#include "commands/pwd_command.h"
#include "commands/cdup_command.h"
#include "commands/delete_command.h"

static void register_commands(void)
{
    register_user_command();
    register_password_command();
    register_quit_command();
    register_cwd_command();
    register_pwd_command();
    register_cdup_command();
    register_delete_command();
}

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
    register_commands();
    if (!ftp_server_start(server)) {
        ftp_server_destroy(server);
        return 84;
    }
    ftp_server_destroy(server);
    return 0;
}
