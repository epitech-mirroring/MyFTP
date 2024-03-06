/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include "commands/cwd_command.h"

void register_cwd_command(void)
{
    ftp_command_t *cwd_command = malloc(sizeof(ftp_command_t));

    cwd_command->name = "cwd";
    cwd_command->expected_args_nb = 1;
    cwd_command->callback = &cwd_callback;
    cwd_command->help = "Change working directory";
    ftp_command_registry(true, cwd_command);
}

bool is_subdir(const char *parent_dir, const char *sub_dir)
{
    char *real_parent_dir = realpath(parent_dir, NULL);
    char *real_sub_dir = realpath(sub_dir, NULL);
    bool result = false;

    if (real_parent_dir == NULL || real_sub_dir == NULL) {
        free(real_parent_dir);
        free(real_sub_dir);
        return result;
    }
    result = strncmp(real_parent_dir, real_sub_dir,
        strlen(real_parent_dir)) == 0;
    free(real_parent_dir);
    free(real_sub_dir);
    return result;
}

static char *get_final_path(char *path, char *actual_path)
{
    char *final_path = NULL;

    if (strchr(path, '/') == 0) {
        final_path = strdup(path);
    } else {
        final_path = malloc(strlen(actual_path) + strlen(path) + 2);
        strcpy(final_path, actual_path);
        strcat(final_path, "/");
        strcat(final_path, path);
    }
    return final_path;
}

void cwd_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *path = args[0];
    char *final_path = get_final_path(path, client->wd_path);
    DIR *dir;

    dir = opendir(final_path);
    if (!dir) {
        ftp_client_send(client, "550 Failed to change directory.\r\n");
    }
    if (is_subdir(server->path, final_path)) {
        closedir(client->working_dir);
        client->working_dir = dir;
        free(client->wd_path);
        client->wd_path = realpath(final_path, NULL);
        ftp_client_send(client, "250 Directory successfully changed.\r\n");
    } else {
        closedir(dir);
        free(final_path);
        ftp_client_send(client, "550 Failed to change directory.\r\n");
    }
}
