/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <sys/stat.h>
#include "commands/list_command.h"

void register_list_command(void)
{
    ftp_command_t *list_command = malloc(sizeof(ftp_command_t));

    list_command->name = "list";
    list_command->expected_args_nb_min = 0;
    list_command->expected_args_nb_max = 1;
    list_command->callback = &list_callback;
    list_command->help = "List files in the current directory";
    list_command->needs_auth = true;
    ftp_command_registry(true, list_command);
}

static char *concat_path(char *path, char *string)
{
    char *new_path = malloc((strlen(path) + strlen(string) + 2) * sizeof(char));
    char *re;

    strcpy(new_path, path);
    strcat(new_path, "/");
    strcat(new_path, string);
    re = realpath(new_path, NULL);
    free(new_path);
    return re;
}

void list_callback(ftp_server_t *server, ftp_client_t *client, char **args)
{
    char *path;
    struct stat path_stat;
    struct dirent *dir;
    DIR *dirp;

    if (args[0] != NULL) {
        path = concat_path(client->wd_path, args[0]);
    } else {
        path = realpath(client->wd_path, NULL);
    }
    stat(path, &path_stat);
    if (S_ISDIR(path_stat.st_mode)) {
        dirp = opendir(path);
        while ((dir = readdir(dirp)) != NULL) {
            ftp_client_send(client, dir->d_name);
            ftp_client_send(client, "\r\n");
        }
        ftp_client_send(client, "226 Transfer complete.\r\n");
        closedir(dirp);
    } else {
        ftp_client_send(client, "550 Failed to open directory.\r\n");
    }
}
