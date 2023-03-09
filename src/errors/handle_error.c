/*
** EPITECH PROJECT, 2023
** handle_error
** File description:
** handle_error
*/

#include "server.h"

void handle_select_errors(int activity)
{
    if ((activity < 0) && (errno != EINTR))
        printf("select error");
}

int check_errors(int argc, char **argv)
{
    if (!argv || !argv[1] || !argv[2])
        return EPITECH_ERROR;

    char *error_message = "USAGE: ./myftp port path\n\tport is the port \
        number on which the server socket listens\n\tpath is the path to \
        the home directory for the Anonymous user\n";

    if (argc == 1 || strcmp(argv[1], "-help") == 0) {
        printf(error_message);
        return 1;
    }

    if (argc != 3)
        return EPITECH_ERROR;
    if (atoi(argv[1]) == 0)
        return EPITECH_ERROR;
    if (chdir(argv[2]) == -1)
        return EPITECH_ERROR;
    return 0;
}
