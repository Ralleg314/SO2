#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2)
{
  int *num1, *num2;

  num1 = (int *) p1;
  num2 = (int *) p2;

  if (*num1 < *num2)
    return -1;
  if (*num1 > *num2)
    return 1;
  return 0;
}

int main(void)
{
  int i;
  int vector[8] = {8, 4, 2, 3, 5, 6, 8, 5};

  qsort(vector, 8, sizeof(int), compara);

  printf("El vector ordenat és ");

  for(i = 0; i < 8; i++)
    printf("%d ", vector[i]);
  
  printf("\n");

  return 0;
}
