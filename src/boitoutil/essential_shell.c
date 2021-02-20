/**
 * @file essential_shell.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "vars.h"
#include "essential_shell.h"
#include "oui-dire.h"

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
 * native_command(): vérifie si la commande entrée par l’utilisateur
 * est implémenté dans le terminal
 * @command: la commande et ses arguments à vérifier
 *
 * Vérifie si la commande entrée par l’utilisateur est native.
 * Si elle l’est, le programme appelle la fonction pour exécuter la commande
 * en lui passant en paramètre les arguments de la commande.
 *
 * Return: 0 si la commande n’est pas native
 *         1 si la commande est native
 */
int native_command(char *command[])
{
  int ret = 1; /* 0 si commande non native */
  if (!strcmp(command[0], "cd"))
    change_dir(command[1]);
  if (!strcmp(command[0], "ouï-dire") || !strcmp(command[0], "oui-dire")
      || !strcmp(command[0], "echo"))
  {
    char *tmp = calloc(MAX_LENGTH, sizeof(char));
    int i = 1;
    while (command[i] != NULL)
    {
      strcat(tmp, command[i]);
      *(tmp + strlen(tmp)) = ' ';
      i++;
    }
    if (i == 2)
      *(tmp + strlen(tmp) - 1) = '\0';
    echo(tmp);
  }
  else
    ret = 0;
  return ret;
}

/**
 * change_dir(): fonction pour implémenter la commande cd
 * @dir: le répertoire à ouvrir
 */
void change_dir(char *dir)
{
  if (chdir(dir))
    error(2, NON_FATAL_ERROR, "Un nom de fichier au lieu d’un dossier \
        a pu etre passé en paramètres.");
}
