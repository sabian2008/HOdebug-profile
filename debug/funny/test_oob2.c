#include <stdlib.h>
#include <stdio.h>

//#define DIM 1039596

#define DIM 103


int main(int argc, char *argv[])
{
  float *a;
  int i;
  int mydim = DIM;
#ifdef DEBUG
  char *errmsg;
#endif


  a = (float *)malloc(sizeof(float)*mydim);
#ifdef DEBUG
  errmsg = (char *)malloc(sizeof(char)*1024);
  sprintf(errmsg, "I'm HERE !!!! \n");
#endif

#ifdef DEBUG
  printf("%s", errmsg);
#endif

  for(i=0; i<mydim; i++)
    {
      a[i+1000] = a[i];
    }

  printf("a = %f \n", a[0]);

  free(a);
#ifdef DEBUG
  free(errmsg);
#endif

  return(EXIT_SUCCESS);
}
