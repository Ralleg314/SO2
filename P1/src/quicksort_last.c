#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1, const void *p2)
{
  char *str1, *str2;
  int last1=1, last2=1;

  str1 = *((char **) p1); 
  str2 = *((char **) p2);

  if(str1[strlen(str1)-last1]<str2[strlen(str2)-last2])
      return -1;
  if(str1[strlen(str1)-last1]>str2[strlen(str2)-last2])
      return 1;
  return 0;
}

char* slice_str(const char * str, size_t end)
{
    const size_t len = strlen(str);
    char *buffer;
    buffer = (char*)malloc((len+1)*sizeof(char));
    
    size_t j = 0;
    for ( size_t i = 0; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
    return buffer;
}


int main()
{
   FILE *fp;
   int longFile;
   char str[100];
   char **vector;
   int i;   

   /* opening file for reading */
   fp = fopen("../dades/strings.txt" , "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   //cuantas lineas hay
   longFile = atoi(fgets(str, 100, fp));
   vector = (char **) malloc(longFile*sizeof(char[100]));
   if(vector==NULL){
	return 1;
   }
   for(i=longFile; i>=0; i--)
   {
      fgets(str, 100, fp);
      //guardar menos el ultimo caracter (es un salto de linea)
      vector[i-1] = slice_str(str,strlen(str)-2);
   }
   
   fclose(fp);
   
   qsort(vector, longFile, sizeof(char*), compara);
   
   for(i=0; i<longFile;i+=100)printf("%s\n",vector[i]);
   
   return(0);
}
