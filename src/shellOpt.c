/** 
 * @file shellOpt.c
 * @author rick <rick@gnous.eu>
 * @date 2021
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int pid;
  char *args[MAX_LENGTH];
  char *command[MAX_LENGTH];
  int my_pipe[2];
  if (pipe(my_pipe) == -1)
  {
    printf("erreur pipe");
    return 1;
  }
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    command[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
  }

  parse_char(args, '|');

  int index = 0;
  while (strcmp(args[0], "exit"))
  {
    while (args[index] != NULL)
    {
      pid = fork();
      if (!pid)
      {
        tok_space(args[index], command, ' ');
        if (args[1] != NULL) 
        {
          if (args[index+1] == NULL)
            dup2(my_pipe[0], STDIN_FILENO);
          else if (index == 0)
            dup2(my_pipe[1], STDOUT_FILENO);
          /*else {
            dup2(my_pipe[0], STDIN_FILENO);
            dup2(my_pipe[1], STDOUT_FILENO);
          }*/
          close(my_pipe[0]);
          close(my_pipe[1]);
        }

        execvp(command[0], command);
        return 0;
      }
      else 
      {
        if (args[index + 1] == NULL)
        {
          close(my_pipe[1]);
          close(my_pipe[0]);
          waitpid(pid, NULL, 0);
        }
          index++;
      }
    }

    for (int i = 0; i < MAX_LENGTH; i++)
    {
      free(args[i]);
      free(command[i]);
      args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
      command[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    }
    parse_char(args, '|');
    if (pipe(my_pipe) == -1)
    {
      printf("erreur sur le pipe");
      return 1;
    }
    index = 0;
  }

  for (int i = 0; i < MAX_LENGTH; i++)
  {
    free(command[i]);
    free(args[i]);
  }
  return 0;
}
