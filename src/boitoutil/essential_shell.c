/**
 * @file essential_shell.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "essential_shell.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * error(): gère les erreurs selon leur code et leur type
 * @code: code de l’erreur, voir les différents codes plus bas
 * @type: NON_FATAL_ERROR pour continuer l’exécution
 *        FATAL_ERROR pour stoper le programme 
 * @message: message à afficher pour + d’infos ou erreur non implémentée
 *
 * 1  erreur lors de la création des pipes
 */
void error(int code, int type, char *message) 
{
  switch (code)
  {
    case 1:
      printf("Erreur lors de la création des pipes.\n");
      break;

    default:
      if (message == NULL)
        printf("Erreur inconnue.\n");
      else
        printf("%s\n", message);
  }

  if (message != NULL)
    printf("Message complémentaire :\n%s\n", message);

  if (type == FATAL_ERROR)
    exit(code);
}
