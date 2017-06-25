//��ʱ��������
#include "time.h"
clock_t start_GPU, finish_GPU,start_CPU, finish_CPU; 
double time_GPU,time_CPU;

#define N 10000
float A[N],B[N],C[N];
float *dev_A,*dev_B,*dev_C;
unsigned int size=N*sizeof(float);

//�߳�/�߳̿�����
const int threadsPerBlock = 1024;//�߳̿�Ĵ�С��Ŀǰ��Щgpu���߳̿����Ϊ512����ЩΪ1024.
const int  num_blocks = (N / threadsPerBlock) + ((N%threadsPerBlock) ? 1 : 0);

//GPU������ʼ��
void init(unsigned int length)
{
	
	// �����ڴ�
	cudaMalloc((void **)&dev_A, size);
	cudaMalloc((void **)&dev_B, size);
	cudaMalloc((void **)&dev_C, size);

	// �����ڴ�
	cudaMemcpy(dev_A, A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_B, B, size, cudaMemcpyHostToDevice);

}
