/**
 * @file essential_shell.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "essential_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * error(): gère les erreurs selon leur code et leur type
 * @code: code de l’erreur, voir les différents codes plus bas
 * @type: NON_FATAL_ERROR pour continuer l’exécution
 *        FATAL_ERROR pour stoper le programme 
 * @message: message à afficher pour + d’infos ou erreur non implémentée
 *
 * 1  erreur lors de la création des pipes
 * 2  chemin inexistant (pour cd)
 */
void error(int code, int type, char *message) 
{
  switch (code)
  {
    case 1:
      printf("Erreur lors de la création des pipes.\n");
      break;
    case 2:
      printf("Chemin inexistant.\n");
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

/**
 * change_dir(): fonction pour vérifier si la commande est un cd
 * @args: la liste des arguments de la commade 
 *
 * Return: 0 si ce n’est pas un cd, 1 sinon
 */
int change_dir(char *args[])
{
  int ret = 0; /* 1 si cd */

  if (!strncmp(args[0], "cd", 2))
  {
    ret = 1;
    if (chdir(args[1]))
      error(2, NON_FATAL_ERROR, "Un nom de fichier au lieu d’un dossier \
          a pu etre passé en paramètres.");
  }

  return ret;
}
