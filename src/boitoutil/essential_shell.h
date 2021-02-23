/**
 * Header pour la bibliothèque permettant d’avoir des 
 * outils essentiels pour le shell tel que la fonction pour 
 * afficher des erreurs.
 * @file essential_shell.h
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include <unistd.h>

#ifndef _ESSHELL_
#   define _ESSHELL_

#define SHELL rishtik
#define FATAL_ERROR 1
#define NON_FATAL_ERROR 0

#define ERR_PIPE_CREATION 200   /* erreur lors de la création des pipes */
#define ERR_FORK 201            /* erreur lors du fork */

extern pid_t pid;
extern int exit_code;

int native_command(char *command[]);
void change_dir(char *command[]);
//void thus_exit(char *command[])
void ctrl_c_handler();
void error(int code, int type, char *message);

#endif
