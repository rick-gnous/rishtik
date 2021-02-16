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
 * @user_input: string où sera enregistrée l’entrée de l’utilisateur
 */
char* get_input()
{
  char *buffer = (char *) malloc(MAX_LENGTH);
  memset(buffer, 0, MAX_LENGTH);

  printf("\n> ");
  fgets(buffer, MAX_LENGTH, stdin);
  while (buffer[0] == '\n') 
  {
    printf("\n> ");
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
  char *token = strtok(user_input, &find);

  int i = 0;
  while (token != NULL && i < MAX_LENGTH)
  {
    strcpy(args[i], token);
    i++;
    token = strtok(NULL, &find);
  }

  // le dernier argument doit être NULL
  // car il est vide et provoque une erreur si non NULL
  free(args[i]);
  args[i] = NULL;

  free(token);
  free(user_input);
}

/**
 * tok_space(): Découpe la chaine orig et met chaque mot dans le tableau dest
 * @orig: chaine à découper
 * @dest: tableau de string où sera stocker les mots
 *
 * La chaine de caractères orig est découper avec les espaces et chaques
 * mots sont mis dans le tableau dest.
 */
void tok_space(char *orig, char *dest[])
{
  char find = ' ';

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
