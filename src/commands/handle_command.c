/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"

void handle_pasv(client_t *clients, int index)
{
    send_response(clients[index].socket,
        "227 Entering Passive Mode (127, 0, 0, 1, 0, 21).\n");
}

void handle_port(client_t *clients, int index)
{
    send_response(clients[index].socket, "200 PORT command successful.\n");
}

void handle_command_three(client_t *clients, int index,
    char *command, int found)
{
    if (strcasecmp(command, "HELP") == 0) {
        send_response(clients[index].socket, "214 Help message.\n");
        found++;
    }
    if (strcasecmp(command, "PASV") == 0) {
        handle_pasv(clients, index);
        found++;
    }
    if (strcasecmp(command, "PORT") == 0) {
        handle_port(clients, index);
        found++;
    }
    if (strcasecmp(command, "QUIT") == 0) {
        send_response(clients[index].socket, "221 Goodbye.\n");
        handle_disconnect(clients, clients[index].socket, index);
        found++;
    }
    if (found == 0)
        send_response(clients[index].socket, "500 Unknown command.\n");
}

void handle_command_two(client_t *clients, int index, char *command,
    int found)
{
    if (strcasecmp(command, "CWD") == 0) {
        handle_cwd(clients, index);
        found++;
    }
    if (strcasecmp(command, "NOOP") == 0) {
        send_response(clients[index].socket, "200 NOOP command okay.\n");
        found++;
    }
    if (strcasecmp(command, "PWD") == 0) {
        handle_pwd(clients, index);
        found++;
    }
    if (strcasecmp(command, "CDUP") == 0) {
        handle_cdup(clients, index);
        found++;
    }
    handle_command_three(clients, index, command, found);
}

void handle_command(client_t *clients, int index, char *buffer)
{
    char *command = strtok(buffer, " \r\n");
    int found = 0;

    if (!command || strlen(command) == 0) {
        send_response(clients[index].socket, "500 Unknown command.\n");
        return;
    }
    if (strcasecmp(command, "SYST") == 0) {
        send_response(clients[index].socket, "215 UNIX Type: L8\n");
        found++;
    }
    if (strcasecmp(command, "DELE") == 0) {
        handle_dele(clients, index, command);
        found++;
    }
    handle_command_two(clients, index, command, found);
}
