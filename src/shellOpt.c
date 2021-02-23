/** 
 * @file shellOpt.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "vars.h"
#include "parser.h"
#include "essential_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
  /** commands contient l’entrée utilisateur parsée avec | :
   *  ls | wc -l -> [ls, wc -l]
   *
   *  args contient une commande à la fois avec ses arguments séparés
   *  par les espaces : 
   *  ls -R test -> [ls, -R, test]
   */
  char *commands[MAX_LENGTH]; 
  char *args[MAX_LENGTH]; 

  int result, index = 0;
  int my_pipe[2];

  /* init pour la gestion du ctrl c */
  struct sigaction ctrc_handler;
  ctrc_handler.sa_handler = ctrl_c_handler;
  sigemptyset(&ctrc_handler.sa_mask);
  ctrc_handler.sa_flags = 0;

  sigaction(SIGINT, &ctrc_handler, NULL);

  setenv("HELLO", "test", 1); /* juste un test */

  if (pipe(my_pipe) == -1)
    error(ERR_PIPE_CREATION, FATAL_ERROR, NULL);

  for (int i = 0; i < MAX_LENGTH; i++)
  {
    args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    commands[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
  }

  while (!need_exit && !get_command(commands, '|'))
  {
    while (commands[index] != NULL)
    {
      parse_string(commands[index], args, ' ');
      if (!native_command(args)) /* si la commande demandée n’est pas native */
      {
        pid = fork();
        if (pid < 0)
          error(ERR_FORK, FATAL_ERROR, NULL);

        if (!pid) /* le fils */
        {
          if (commands[index+1] == NULL) 
          {
            dup2(my_pipe[0], STDIN_FILENO);
            close(my_pipe[1]);
          }
          else if (index == 0)
          {
            dup2(my_pipe[1], STDOUT_FILENO);
            close(my_pipe[0]);
          }
          else
            fclose(fdopen(my_pipe[0], "w"));
          /* si la commande est intermédiaire dans le pipe, on vide le buffer
           * de sortie NE MARCHE PAS */

          execvp(args[0], args);
          exit(errno);
        }

        /* lorsqu’on arrive à la dernière commande, on peut fermer le pipe et 
         * attendre le dernier processus */
        if (commands[index + 1] == NULL)
        {
          close(my_pipe[0]);
          close(my_pipe[1]);
        }
        waitpid(pid, &result, 0);

        if(WIFEXITED(result)) /* on récupère le code de retour pour afficher l’erreur */
          error(WEXITSTATUS(result), NON_FATAL_ERROR, NULL);
      }

      for (int i = 0; i < MAX_LENGTH; i++)
      {
        free(args[i]);
        args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
      }
      index++;
    }

    /* remise à 0 des entrées, des commandes, des pipes et de l’index */
    for (int i = 0; i < MAX_LENGTH; i++)
    {
      free(args[i]);
      free(commands[i]);
      args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
      commands[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    }

    if (pipe(my_pipe) == -1)
      error(ERR_PIPE_CREATION, FATAL_ERROR, NULL);
    index = 0;
  }

  for (int i = 0; i < MAX_LENGTH; i++)
  {
    free(commands[i]);
    free(args[i]);
  }
  return exit_code;
}
