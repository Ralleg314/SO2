#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1, const void *p2)
{
  int *num1, *num2;

  num1 = (int *) p1;
  num2 = (int *) p2;

  if (*num1 < *num2)
    return 1;
  if (*num1 > *num2)
    return -1;
  return 0;
}

char* slice_str(const char * str, size_t end)
{
    const size_t len = strlen(str);
    char *buffer;
    buffer = (char*)malloc((len+1)*sizeof(char));
    
    size_t i, j = 0;
    for ( i = 0; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
    return buffer;
}

int main(void)
{
  FILE *fp;
   int longFile;
   char str[100];
   int *vector;
   int i;   

   /* opening file for reading */
   fp = fopen("../dades/integers.txt" , "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   //cuantas lineas hay
   longFile = atoi(fgets(str, 100, fp));
   vector = (int *) malloc(longFile*sizeof(int));
   if(vector==NULL){
	return 1;
   }
   for(i=0; i<longFile; i++)
   {
      fgets(str, 100, fp);
      //guardar menos el ultimo caracter (es un salto de linea)
      vector[i] = atoi(slice_str(str,strlen(str)-1));
   }

   fclose(fp);
   
   qsort(vector, longFile, sizeof(int), compara);
   
   for(i=0; i<longFile;i+=100)printf("%d\n",vector[i]);
   
   return(0);
}
