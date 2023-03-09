/*
** EPITECH PROJECT, 2023
** directories_gestion
** File description:
** directories
*/

#include "server.h"

void handle_pwd(client_t *clients, int index)
{
    send_response(clients[index].socket, "257 \"");
    send_response(clients[index].socket, clients[index].path);
    send_response(clients[index].socket, "\"\n");
}

void handle_cwd(client_t *clients, int index)
{
    char *path = strtok(NULL, " \r");

    if (!path || chdir(clients[index].path) == -1 || chdir(path) == -1)
        send_response(clients[index].socket,
            "550 Failed to change directory.\n");
    else {
        clients[index].path = getcwd(NULL, 0);
        send_response(clients[index].socket,
            "250 Directory successfully changed.\n");
    }
}

void handle_cdup(client_t *clients, int index)
{
    if (chdir(clients[index].path) == -1 || chdir("..") == -1)
        send_response(clients[index].socket,
            "550 Failed to change directory.\n");
    else {
        clients[index].path = getcwd(NULL, 0);
        send_response(clients[index].socket,
            "250 Directory successfully changed.\n");
    }
}

void handle_dele(client_t *clients, int index, char *command)
{
    command = strtok(NULL, " \r\n");
    if (command == NULL) {
        send_response(clients[index].socket, "501 Missing argument.\n");
        return;
    }
    chdir(clients[index].path);
    if (remove(command) == 0)
        send_response(clients[index].socket, "250 Requested file action okay, "
            "completed.\n");
    else
        send_response(clients[index].socket, "550 Requested action not taken. "
            "File unavailable.\n");
}
