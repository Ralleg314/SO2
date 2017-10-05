#include <stdio.h>
#include <string.h> // per la funcio strlen
#include <ctype.h>  // per les funcions isalpha, isdigit, ...

#define MAXCHAR 100

int main(void)
{
  int i, len;
  char cadena[MAXCHAR];

  printf("Introdueix la cadena a processar: ");
  fgets(cadena, MAXCHAR, stdin);

  len = strlen(cadena);
  for(i = 0; i < len; i++)
  {
    printf("Posicio: %02i, caracter: %c, es de tipus: ", i, (char) cadena[i]);

    if (isalpha(cadena[i]))
      printf("lletra");
    else if (isdigit(cadena[i]))
      printf("nombre");
    else if (ispunct(cadena[i]))
      printf("signe de puntuacio");
    else if (isspace(cadena[i]))
      printf("espai o retorn de carro");
    else 
      printf("no se sap");

    printf("\n");
  }
}

