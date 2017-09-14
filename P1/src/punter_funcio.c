#include <stdio.h>
#include <math.h>

double func1(int a)
{
  return sqrt((double) a);
}

double func2(int b)
{
  return log((double) b);
}

int main(void) 
{   
  double ret;
  int selecciona = 1;
  double (*myfunc)(int);

  if (selecciona == 1)
    myfunc = func1;
  else 
    myfunc = func2;

  ret = myfunc(5);

  printf("Resultat: %e", ret);

  return 0;
}
