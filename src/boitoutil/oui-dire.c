/**
 */

#include "oui-dire.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void echo(char *args)
{
  char tmp = *args;
  int i = 0;
  while (tmp != '\0')
  {
   putchar(tmp);
   i++;
   tmp = *(args + i);
  }
  putchar('\n');
}
