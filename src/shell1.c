#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "mylib.h"

int main()
{
  char *user_input = (char *) malloc(MAX_LENGTH);
  int result, pid;
  get_input(user_input);
  while (strcmp(user_input, "exit"))
  {
    pid = fork();

    if (!pid)
    {
      execlp(user_input, user_input, NULL);
      return 0;
    }
    else 
      wait(&result);

    get_input(user_input);
  }
  free(user_input);
  return 0;
}
