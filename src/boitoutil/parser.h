/**
 * Header pour la bibliothèque servant à parser et récupérer l’entrée
 * utilisateur.
 * @file parser.h
 * @author rick <rick@gnous.eu>
 * @date 2021
 * Bibliothèque pour le shell rishtik
 */

#ifndef _PARSER_H_
#   define _PARSER_H_

char* get_input();
int get_command(char *args[], char find);
void parse_string(char *args,char  *commands[], char find);
int detect_exit(char *command);

#endif
