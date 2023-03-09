/*
** EPITECH PROJECT, 2023
** checklogi
** File description:
** check_login
*/

#include "server.h"

void check_login(client_t *clients, int i, char *buffer)
{
    int client_socket = clients[i].socket;
    if (strncmp(buffer, "QUIT", 4) == 0) {
        send_response(clients[i].socket, "221 Goodbye.\n");
        handle_disconnect(clients, clients[i].socket, i);
        return;
    }
    if (strncmp(buffer, "USER Anonymous", 14) != 0) {
        send_response(client_socket, "530 Invalid username or password.\n");
        return;
    }
    send_response(client_socket, "331 Please specify the password.\n");
    read_method(client_socket, buffer);
    if (strncmp(buffer, "PASS ", 5) != 0)
        send_response(client_socket, "530 Invalid username or password.\n");
    else {
        send_response(client_socket, "230 User logged in, proceed.\n");
        clients[i].logged_in = 1;
    }
}
