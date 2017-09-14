#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1, const void *p2)
{
  char *str1, *str2;

  str1 = *((char **) p1); 
  str2 = *((char **) p2);

  return strcmp(str1,str2);
}

int main(void)
{
  int i;
  char *vector[8] = {"hola", "sistemes", "operatius", "dos", "cadena", 
                     "quicksort", "canonada", "compara"};

  qsort(vector, 8, sizeof(char *), compara);

  printf("El vector ordenat és\n");

  for(i = 0; i < 8; i++)
    printf("%s\n", vector[i]);

  printf("\n");

  return 0;
}
