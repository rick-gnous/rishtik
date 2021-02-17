/**
 * Header pour la bibliothèque permettant d’avoir des 
 * outils essentiels pour le shell tel que la fonction pour 
 * afficher des erreurs.
 * @file essential_shell.h
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#ifndef _ESSHELL_
#   define _ESSHELL_

#define SHELL rishtik
#define FATAL_ERROR 1
#define NON_FATAL_ERROR 0

void error(int code, int type, char *message);

#endif
