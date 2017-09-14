#include <stdio.h>

int main()
{
   FILE *fp;
   char str[100];

   /* opening file for reading */
   fp = fopen("file.txt" , "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   if( fgets (str, 100, fp)!=NULL ) 
   {
      /* writing content to stdout */
      puts(str);
   }
   fclose(fp);
   
   return(0);
}
