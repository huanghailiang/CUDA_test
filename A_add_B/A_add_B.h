#include "stdio.h"
#include "memcpy.h"

//��������ӵ�GPU����
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
	
	
	
	
	//ִ�к˺���
	AaddB<<<num_blocks, threadsPerBlock>>>(dev_A, dev_B, dev_C, length);

	// �����������
	cudaMemcpy(C , dev_C, size, cudaMemcpyDeviceToHost);

	//�ͷ��ڴ�
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);

	//����ֵ
	return C;
	
}

