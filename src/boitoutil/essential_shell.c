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
#include <errno.h>
//#include <sys/types.h>
#include <signal.h>

pid_t pid;
int exit_code;

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
    change_dir(command);
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
void change_dir(char *command[])
{
  char *dir = command[1];
  if (chdir(dir) < 0)
  {
    int code = errno;
    char *txt_error = calloc(MAX_LENGTH, sizeof(char));
    strcat(txt_error, command[0]);
    strcat(txt_error, ": ");
    strcat(txt_error, dir);
    error(code, NON_FATAL_ERROR, txt_error);
    free(txt_error);
  }
}

//void thus_exit(char *command[])
//{
//  exit_code = 0;
//}

void ctrl_c_handler()
{
  //kill(pid, SIGTERM);
  //kill(pid, SIGKILL);
  kill(getpid(), SIGCHLD);
  printf("\n");
}

/**
 * error(): gère les erreurs selon leur code et leur type
 * @code: code de l’erreur, voir les différents codes dans le fichier .h
 * @type: NON_FATAL_ERROR pour continuer l’exécution
 *        FATAL_ERROR pour stoper le programme
 * @message: message à afficher pour + d’infos ou erreur non implémentée
 */
void error(int code, int type, char *message)
{
  if (code == 0)
    return;

  /* const char *txt_error = strerror(code); */
  if (errno == EINVAL)
  {
    switch (code)
    {
      case ERR_PIPE_CREATION:
        fprintf(stderr, "Erreur lors de la création des pipes.\n");
        break;
      case ERR_FORK:
        fprintf(stderr, "Le fork a échoué, le processus enfant a été avorté.\n");
        break;

      default:
        if (message == NULL)
          fprintf(stderr, "Erreur inconnue.\n");
        else
          fprintf(stderr, "%s\n", message);
    }
    if (message != NULL)
      fprintf(stderr, "Message complémentaire :\n%s\n", message);
  }
  else
  {
    if (message != NULL)
    {
      errno = code;
      perror(message);
    }
    /* else
      fprintf(stderr, "%s\n", txt_error); */
  }

  if (type == FATAL_ERROR)
    exit(code);
}
