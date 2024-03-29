/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <printf.h>
#include <unistd.h>
#include "ftp_server.h"
#include "commands/user_command.h"
#include "commands/password_command.h"
#include "commands/quit_command.h"
#include "commands/cwd_command.h"
#include "commands/pwd_command.h"
#include "commands/cdup_command.h"
#include "commands/delete_command.h"
#include "commands/pasv_command.h"
#include "commands/list_command.h"
#include "commands/port_command.h"
#include "commands/store_command.h"
#include "commands/retrieve_command.h"
#include "commands/help_command.h"
#include "commands/noop_command.h"

static void register_commands(void)
{
    register_user_command();
    register_password_command();
    register_quit_command();
    register_cwd_command();
    register_pwd_command();
    register_cdup_command();
    register_delete_command();
    register_pasv_command();
    register_list_command();
    register_port_command();
    register_store_command();
    register_retrieve_command();
    register_help_command();
    register_noop_command();
}

static bool check_args(char *arg_1, char *arg_2)
{
    if (arg_1 == NULL || arg_2 == NULL)
        return false;
    for (int i = 0; arg_1[i] != '\0'; i++)
        if (arg_1[i] < '0' || arg_1[i] > '9')
            return false;
    if (atoi(arg_1) == 0 || atoi(arg_1) > 65535)
        return false;
    if (access(arg_2, F_OK) == -1)
        return false;
    if (access(arg_2, R_OK) == -1)
        return false;
    if (chdir(arg_2) == -1)
        return false;
    return true;
}

int main(int argc, char **argv)
{
    ftp_server_t *server;
    int r = 0;

    if (argc != 3 ||
        (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport is the port number on which the server"
            " socket listens\n");
        printf("\tpath is the path to the home directory for"
            " the Anonymous user\n");
        return strcmp(argv[1], "--help") == 0 ? 0 : 84;
    }
    if (!check_args(argv[1], argv[2]))
        return 84;
    server = ftp_server_create(atoi(argv[1]), argv[2]);
    register_commands();
    r = !ftp_server_start(server) ? 84 : 0;
    ftp_server_destroy(server);
    return r;
}
