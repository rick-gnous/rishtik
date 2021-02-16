/**
 * @file parser.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * get_input(): Permet de récupérer la saisie de l’utilisateur
 *
 * Return: Entrée utilisateur
 */
char* get_input()
{
  char *buffer = (char *) malloc(MAX_LENGTH);
  memset(buffer, 0, MAX_LENGTH);
  buffer[0] = '\n';

  while (buffer[0] == '\n') 
  {
    printf("> ");
    fgets(buffer, MAX_LENGTH, stdin);
  }
  buffer[strlen(buffer)-1] = '\0'; /* pour ne pas avoir un retour à la ligne */
  return buffer;
}

/**
 * parse_char(): Récupère l’entrée de l’utilisateur avant de la parser
 * @args: Tableau de string
 * @find: caractère utilisé pour parser
 *
 * Récupère l’entrée de l’utilisateur avant de la parser avec le caractère
 * find. Chaque string sera mise dans une case de args.
 */
void parse_char(char *args[], char find)
{
  char *user_input = get_input();
  tok_space(user_input, args, find);
  free(user_input);
}

/**
 * tok_space(): Découpe la chaine orig et met chaque mot dans le tableau dest
 * @orig: chaine à découper
 * @dest: tableau de string où sera stocker les mots
 * @find: caractère à utilise pour parser la chaine orig
 *
 * La chaine de caractères orig est découpée selon le caractère find
 * et chaques mots sont mis dans le tableau dest.
 */
void tok_space(char *orig, char *dest[], char find)
{
  char *token = strtok(orig, &find);

  int i = 0;
  while (token != NULL && i < MAX_LENGTH)
  {
    strcpy(dest[i], token);
    i++;
    token = strtok(NULL, &find);
  }

  // le dernier argument doit être NULL
  // car il est vide et provoque une erreur si non NULL
  free(dest[i]);
  dest[i] = NULL;

  free(token);
}
