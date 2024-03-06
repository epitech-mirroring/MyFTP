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

void ftp_command_destroy_prepared(ftp_prepared_command_t *prepared_command)
{
    free(prepared_command->args);
    free(prepared_command);
}

ftp_prepared_command_t *ftp_command_prepare(char *command)
{
    ftp_prepared_command_t *prepared_command = malloc(sizeof(
            ftp_prepared_command_t));

    if (prepared_command == NULL) {
        perror("Cannot allocate memory for the prepared command\n");
        return NULL;
    }
    prepared_command->name = strtok(command, " ");
    for (size_t i = 0; i < strlen(prepared_command->name); i++)
        prepared_command->name[i] = (char)tolower(prepared_command->name[i]);
    prepared_command->args_nb = 0;
    prepared_command->args = malloc(sizeof(char *) * 10);
    for (size_t i = 0; i < 10; i++) {
        prepared_command->args[i] = strtok(NULL, " ");
        if (prepared_command->args[i] == NULL) {
            prepared_command->args_nb = i;
            break;
        }
    }
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
    return prepared;
}
