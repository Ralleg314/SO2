#include <stdio.h>
#include <string.h> // per la funcio strlen
#include <ctype.h>  // per les funcions isalpha, isdigit, ...
#include <stdlib.h>

#define MAXCHAR 100

int main(void)
{
  int i, j, len;
  int inicio=0, fin;
  int dist;
  char cadena[MAXCHAR], *palabra;

  printf("Introdueix la cadena a processar: ");
  fgets(cadena, MAXCHAR, stdin);

  len = strlen(cadena);
  for(i = 0; i < len; i++)
  {
    //printf("%d %d \n", inicio, i);
    if(!isalpha(cadena[i]) && !isdigit(cadena[i])){
        fin=i;
        dist=fin-inicio;
        palabra = (char*)malloc(dist*sizeof(char));
        for(j=0;j<dist;j++){
            palabra[j]=tolower(cadena[inicio+j]);
        }
        printf("%s\n", palabra);
        inicio=i+1;
        free(palabra);
    }
  }
  
  return 0;
}
