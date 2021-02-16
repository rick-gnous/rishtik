#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 200

char** u_get_input(char* buffer, char* user_input, int i);

int main()
{
  char *buffer = (char *) malloc(MAX_LENGTH);
  char *user_input1 = (char *) malloc(MAX_LENGTH);
  char *user_input2 = (char *) malloc(MAX_LENGTH);
  int pid1, pid2;
  int my_pipe[2];
  int t = pipe(my_pipe);
  if (t == -1)
  {
    printf("erreur à la création du pipe");
    return 1;
  }
  char **args1 = u_get_input(buffer, user_input1, 1);
  char **args2 = NULL;
  while (strcmp(user_input1, "exit") != 0)
  {
    args2 = u_get_input(buffer, user_input2, 2);
    pid1 = fork();

    if (!pid1)
    {
      dup2(my_pipe[1], STDOUT_FILENO);
      close(my_pipe[0]);
      close(my_pipe[1]);
      execvp(user_input1, args1);

      return 0;
    }
    else { 
      pid2 = fork();

      if (!pid2) 
      {
        dup2(my_pipe[0], STDIN_FILENO);
        close(my_pipe[1]);
        close(my_pipe[0]);
        execvp(user_input2, args2);
        return 0;
      }
      else 
      {
        close(my_pipe[0]);
        close(my_pipe[1]);
        waitpid(pid2, NULL, 0);
      }
    }

    free(args1);
    free(args2);
    args1 = u_get_input(buffer, user_input1, 1);
    pipe(my_pipe);
  }
  free(args1);
  free(buffer);
  free(user_input1);
  free(user_input2);
  return 0;
}

char** u_get_input(char* buffer, char* user_input, int j)
{
  printf("\ncommande%d> ", j);
  memset(buffer, 0, MAX_LENGTH);
  memset(user_input, 0, MAX_LENGTH);
  fgets(buffer, MAX_LENGTH, stdin);
  strncpy(user_input, buffer, strlen(buffer)-1);

  char *token = strtok(user_input, " ");
  char **args = (char **) malloc(MAX_LENGTH);
  int i = 0;
  while (token != NULL && i < MAX_LENGTH)
  {
    args[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
  return args;
}
