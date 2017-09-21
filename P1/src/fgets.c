#include <stdio.h>
#include<stdlib.h>
#include<string.h>

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
   for(i=longFile; i>0; i--)
   {
      fgets(str, 100, fp);
      //guardar menos el ultimo caracter (es un salto de linea)
      vector[i-1] = slice_str(str,strlen(str)-1);
      printf("%s", vector[i-1]);
   }
   //este es el ultimo, no tiene salto de linea
   fgets(str, 100, fp);
   vector[0] = str;

   fclose(fp);
   
   return(0);
}
