/** Code de la commande echo
 * @file oui-dire.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "oui-dire.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * echo(): Affiche sur la sortie standart un message
 * @args: message à afficher sur la sortie standart
 */
void echo(char *args)
{
  char tmp = *args;
  int i = 0;
  while (tmp != '\0')
  {
    if (tmp == '$')
    {
      i++;
      i += get_var((args+i), i);
    }
    else
    {
      putchar(tmp);
      i++;
    }

    tmp = *(args + i);
  }
  putchar('\n');
}

int get_var(char *str, int i)
{
  char *tmp = calloc(strlen(str), sizeof(char));
  strcpy(tmp, str);
  char f = ' ';
  char *token = strtok(tmp, &f);
  printf("%s", getenv(token));
  int ret = strlen(token);
  free(tmp);
  return ret;
}
