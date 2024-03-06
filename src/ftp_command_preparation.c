/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ftp_command.h"
#include "utils/my.h"

void ftp_command_destroy_prepared(ftp_prepared_command_t *prepared_command)
{
    for (size_t i = -1; i < prepared_command->args_nb; i++) {
        free(*(prepared_command->args + i));
    }
    free(prepared_command);
}

ftp_prepared_command_t *ftp_command_prepare(char *command)
{
    ftp_prepared_command_t *prepared_command = malloc(sizeof(
            ftp_prepared_command_t));
    char **splitted;

    if (prepared_command == NULL) {
        perror("Cannot allocate memory for the prepared command\n");
        return NULL;
    }
    splitted = my_split(command, ' ');
    if (splitted == NULL) {
        perror("Cannot split the command\n");
        free(prepared_command);
        return NULL;
    }
    prepared_command->name = splitted[0];
    prepared_command->args = splitted + 1;
    prepared_command->args_nb = count_words(command, ' ') - 1;
    return ftp_command_sanitise(prepared_command);
}

ftp_prepared_command_t *ftp_command_sanitise(ftp_prepared_command_t *prepared)
{
    char temp;

    for (size_t i = 0; i < prepared->args_nb; i++) {
        for (size_t j = 0; j < strlen(prepared->args[i]); j++) {
            temp = prepared->args[i][j];
            prepared->args[i][j] = (char) (temp == '\n' || temp == '\r' ?
                '\0' : temp);
        }
    }
    for (size_t i = 0; i < strlen(prepared->name); i++) {
        temp = prepared->name[i];
        prepared->name[i] = (char) (temp == '\n'
            || temp == '\r' ? '\0' : temp);
        prepared->name[i] = (char) tolower(prepared->name[i]);
    }
    return prepared;
}
