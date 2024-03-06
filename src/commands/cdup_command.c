/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include "commands/cdup_command.h"
#include "commands/cwd_command.h"

void register_cdup_command(void)
{
    ftp_command_t *cdup_command = malloc(sizeof(ftp_command_t));

    cdup_command->name = "cdup";
    cdup_command->expected_args_nb = 0;
    cdup_command->callback = &cdup_callback;
    cdup_command->help = "Change to the parent directory";
    cdup_command->needs_auth = true;
    ftp_command_registry(true, cdup_command);
}

void cdup_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *target_path = malloc(strlen(client->wd_path) + strlen("/..") + 1);

    (void)args;
    strcpy(target_path, client->wd_path);
    strcat(target_path, "/..");
    if (!is_subdir(server->path, target_path)) {
        ftp_client_send(client, "550 Permission denied.\r\n");
        free(target_path);
        return;
    }
    free(client->wd_path);
    closedir(client->working_dir);
    client->wd_path = realpath(target_path, NULL);
    free(target_path);
    client->working_dir = opendir(client->wd_path);
    ftp_client_send(client, "200 Directory successfully changed.\r\n");
}