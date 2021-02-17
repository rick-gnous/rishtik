/** 
 * @file shellOpt.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "parser.h"
#include "essential_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

  int pid, index = 0, end = 0; /* end permet de savoir quand s’arreter */
  int my_pipe[2];

  if (pipe(my_pipe) == -1)
    error(1, FATAL_ERROR, NULL);

  for (int i = 0; i < MAX_LENGTH; i++)
  {
    args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    commands[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
  }

  get_command(commands, '|');

  while (strcmp(commands[0], "exit"))
  {
    while (commands[index] != NULL)
    {
        pid = fork();
        if (!pid)
        {
          parse_string(commands[index], args, ' ');
          if (commands[index+1] == NULL)
            dup2(my_pipe[0], STDIN_FILENO);
          else if (index == 0)
            dup2(my_pipe[1], STDOUT_FILENO);
          close(my_pipe[0]);
          close(my_pipe[1]);

          execvp(args[0], args);
          return 0;
        }
        else 
        {
          if (commands[index + 1] == NULL)
          {
            close(my_pipe[1]);
            close(my_pipe[0]);
            waitpid(pid, NULL, 0);
          }
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

    get_command(commands, '|');
    if (pipe(my_pipe) == -1)
      error(1, FATAL_ERROR, NULL);
    index = 0;
  }

  for (int i = 0; i < MAX_LENGTH; i++)
  {
    free(commands[i]);
    free(args[i]);
  }
  return 0;
}
