/**
 * @file parser.h
 * @author rick <rick@gnous.eu>
 * @date 2021
 * Bibliothèque pour le shell rishtik
 */

#ifndef _PARSER_H_
#   define _PARSER_H_

#define MAX_LENGTH 200 /* taille maximum des tableaux utilisés */

char* get_input();
void parse_char(char *args[], char find);
void tok_space(char *args,char  *commands[]);

#endif
