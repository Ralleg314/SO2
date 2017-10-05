#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int main(void)
{
  char	line[MAXLINE];
  FILE	*fpin, *fpout;

  fpin = fopen("fitxer", "r");
  if (!fpin) {
    printf("ERROR: no puc obrir fitxer d'entrada.\n");
    exit(EXIT_FAILURE);
  }

  // Obrim l'aplicacio 'wc'. Es una utilitat de sistema que
  // permet comptar el nombre de linies de text d'un fitxer.
  fpout = popen("wc", "w");
  if (!fpout)
  {
    printf("ERROR: no puc crear canonada.\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(line, MAXLINE, fpin) != NULL) {
    if (fputs(line, fpout) == EOF) {
      printf("ERROR: no puc escriure a la canonada.\n");
      exit(EXIT_FAILURE);
    }
  }

  if (pclose(fpout) == -1)
  {
    printf("ERROR: pclose.\n");
    exit(EXIT_FAILURE);
  }

  printf("L'aplicació ha acabat.\n");

  return 0;
}
