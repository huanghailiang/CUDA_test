#include "a_add_b.h"

int main (void)
{
	cudaMalloc((void **)&dev_c,sizeof(int));
	add<<<1,1>>>(2,7,dev_c);
	cudaMemcpy(&c,dev_c,sizeof(int),cudaMemcpyDeviceToHost);
	printf("2+7=%d\n",c);
	cudaFree(dev_c);
	return 0;
}