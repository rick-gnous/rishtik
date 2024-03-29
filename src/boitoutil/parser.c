/**
 * Code source pour la bibliothèque servant à parser et récupérer l’entrée
 * utilisateur.
 * @file parser.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "vars.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * get_input(): Permet de récupérer la saisie de l’utilisateur
 *
 * Return: Entrée utilisateur ou NULL si ctrl d détecté
 */
char* get_input()
{
  fflush(stdin);
  int stop = 0; /* en cas de ctrl d */
  char *buffer = (char *) calloc(MAX_LENGTH, sizeof(char));
  buffer[0] = '\n';

  while (buffer[0] == '\n' && !stop)
  {
    printf("> ");
    if(fgets(buffer, MAX_LENGTH, stdin) == NULL && errno != EINTR)
      stop++;
    errno = 0; /* réinitialiser le errno pour le prochain fgets */
  }

  if (stop)
  {
    free(buffer);
    buffer = NULL;
    putchar('\n'); /* pour un affichage propre */
  }
  else
    buffer[strlen(buffer)-1] = '\0'; /* pour ne pas avoir un retour à la ligne */

  return buffer;
}

/**
 * get_command(): Récupère l’entrée de l’utilisateur avant de la parser
 * @args: Tableau de string
 * @find: caractère utilisé pour parser
 *
 * Récupère l’entrée de l’utilisateur avant de la parser avec le caractère
 * find. Chaque string sera mise dans une case de args.
 *
 * Return: 0 si tout est OK, 1 sinon
 */
int get_command(char *args[], char find)
{
  int ret = 0;
  char *user_input = get_input();

  if (user_input == NULL)
    ret = 1;
  else
  {
    parse_string(user_input, args, find);
    free(user_input);
  }

  return ret;
}

/**
 * parse_string(): Découpe la chaine orig et met chaque mot dans le tableau dest
 * @orig: chaine à découper
 * @dest: tableau de string où sera stocker les mots
 * @find: caractère à utilise pour parser la chaine orig
 *
 * La chaine de caractères orig est découpée selon le caractère find
 * et chaques mots sont mis dans le tableau dest.
 * S’il y a un \ avant le caractère find, celui-ce sera ignoré.
 */
void parse_string(char *orig, char *dest[], char find)
{
  char *token = strtok(orig, &find);
  int pred = 0, i = 0;

  while (token != NULL && i < MAX_LENGTH)
  {
    if (pred)
    {
      dest[i][strlen(dest[i])-1] = find;
      strcat(dest[i], token);
      pred = 0;
    }
    else
      strcpy(dest[i], token);

    if (dest[i][strlen(dest[i])-1] == '\\')
      pred = 1;
    else
      i++;

    token = strtok(NULL, &find);
  }

  if (pred)
    i++;

  /** le dernier argument doit être NULL
   pour l’utilisation de execvp */
  free(dest[i]);
  dest[i] = NULL;

  //free(token);
}
