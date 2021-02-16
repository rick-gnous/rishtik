#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parser.h"

int main()
{
  int result, pid;
  char *args[MAX_LENGTH];
  for (int i = 0; i < MAX_LENGTH; i++)
    args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));

  parse_char(args, ' ');
  //get_args(args);
  while (strcmp(args[0], "exit"))
  {
    pid = fork();

    if (!pid)
    {
      execvp(args[0], args);
      return 0;
    }
    else 
      wait(&result);

    for (int i = 0; i < MAX_LENGTH; i++)
    {
      free(args[i]);
      args[i] = (char *) calloc(MAX_LENGTH, sizeof(char));
    }
    //get_args(args);
    parse_char(args, ' ');
  }

  for (int i = 0; i < MAX_LENGTH; i++)
    free(args[i]);
  return 0;
}
