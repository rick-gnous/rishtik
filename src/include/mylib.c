#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib.h"

/**
 * @brief Permet de récupérer la commande de l’utilisateur
 *
 * @param user_input entrée de l’utilisateur, contiendrat la commande à exécuter
 */
void get_input(char *user_input)
{
  char *buffer = (char *) malloc(MAX_LENGTH);
  memset(user_input, 0, MAX_LENGTH);
  printf("\n> ");
  fgets(buffer, MAX_LENGTH, stdin);
  while (buffer[0] == '\n') 
  {
    printf("\n> ");
    fgets(buffer, MAX_LENGTH, stdin);
  }
  strncpy(user_input, buffer, strlen(buffer)-1);
  free(buffer);
}

/**
 * @brief récupère l’entrée de l’utilisateur et la découpe
 * selon le caractère passé en paramètre
 *
 * @param args Tableau de string qui sera modifié avec
 * les arguments de la commande
 * @param find Le caractère à utiliser pour découper la chaine
 */
void parse_char(char *args[], char find)
{
  char *user_input = (char *) malloc(MAX_LENGTH);
  get_input(user_input);

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

/*
 * @brief parse la chaine orig avec les espaces et la met dans le tableau dest
 * */
void tok_space(char *orig, char* dest[])
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
