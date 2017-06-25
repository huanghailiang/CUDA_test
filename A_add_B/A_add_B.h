#include "stdio.h"
#include "memcpy.h"

//两数组相加的GPU函数
__device__ void AaddB(const float *A,const float *B,float *C,int length)
{
	const int i=blockDim.x*blockIdx.x+threadIdx.x;
float *Q;
Q=C;
	if (i<length)
	{
		Q[i]=A[i]+B[i];
		
		
	}
C=Q;
}

float *vector_add(float *A,float *B,unsigned int length)
{
	
	
	
	
	//执行核函数
	AaddB<<<num_blocks, threadsPerBlock>>>(dev_A, dev_B, dev_C, length);

	// 结果拷贝回来
	cudaMemcpy(C , dev_C, size, cudaMemcpyDeviceToHost);

	//释放内存
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);

	//返回值
	return C;
	
}

