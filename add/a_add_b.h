#include "stdio.h"

int c;
int *dev_c;


__global__ void add (int a,int b,int *c)
{

	*c=a+b;
}
