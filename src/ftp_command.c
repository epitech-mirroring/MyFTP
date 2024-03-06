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
#include "ftp.h"

ftp_command_t ***ftp_command_registry(bool write, void *data)
{
    static size_t commands_nb = 0;
    static ftp_command_t **commands = NULL;

    if (write) {
        commands_nb++;
        commands = realloc(commands, sizeof(ftp_command_t *)
            * (commands_nb + 1));
        if (commands == NULL) {
            perror("Cannot re-size the command registry\n");
            return NULL;
        }
        commands[commands_nb - 1] = data;
        commands[commands_nb] = NULL;
        return NULL;
    }
    if (commands == NULL) {
        commands = malloc(sizeof(ftp_command_t *) * 1);
        if (commands == NULL) {
            returnWithError("Cannot allocate memory for the command registry\n", NULL);
        }
        commands[0] = NULL;
    }
    return &commands;
}

void ftp_command_destroy_registry(void)
{
    ftp_command_t ***commands = ftp_command_registry(false, NULL);

    for (size_t i = 0; (*commands)[i] != NULL; i++) {
        free((*commands)[i]->name);
        free((*commands)[i]->help);
        free((*commands)[i]);
    }
    free(*commands);
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
    return prepared_command;
}

static void ftp_command_not_implemented(ftp_client_t *client)
{
    dprintf(client->socket, "502 Command not implemented.\r\n");
}

static void ftp_command_unknown(ftp_client_t *client)
{
    dprintf(client->socket, "500 Unknown command.\r\n");
}

static void ftp_command_invalid_args(ftp_client_t *client)
{
    dprintf(client->socket, "501 Invalid number of arguments.\r\n");
}

static void ftp_command_try_execute(ftp_server_t *server, ftp_client_t *client,
    ftp_prepared_command_t *prepared_command, ftp_command_t *command)
{
    if (command->expected_args_nb != prepared_command->args_nb) {
        ftp_command_invalid_args(client);
        return;
    }
    if (command->callback == NULL) {
        ftp_command_not_implemented(client);
        return;
    }
    command->callback(server, client, prepared_command->args);
}

void ftp_command_execute(ftp_server_t *server, ftp_client_t *client,
    char *command)
{
    ftp_command_t ***commands = ftp_command_registry(false, NULL);
    ftp_prepared_command_t *prepared_command = ftp_command_prepare(command);

    if (prepared_command == NULL)
        return;
    for (size_t i = 0; (*commands)[i] != NULL; i++) {
        if (strcmp((*commands)[i]->name, prepared_command->name) == 0) {
            ftp_command_try_execute(server, client, prepared_command,
                (*commands)[i]);
        }
    }
    ftp_command_unknown(client);
}
