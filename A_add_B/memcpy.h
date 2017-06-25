//计时参数定义
#include "time.h"
clock_t start_GPU, finish_GPU,start_CPU, finish_CPU; 
double time_GPU,time_CPU;

#define N 10000
float A[N],B[N],C[N];
float *dev_A,*dev_B,*dev_C;
unsigned int size=N*sizeof(float);

//线程/线程块数量
const int threadsPerBlock = 1024;//线程块的大小。目前有些gpu的线程块最大为512，有些为1024.
const int  num_blocks = (N / threadsPerBlock) + ((N%threadsPerBlock) ? 1 : 0);

//GPU参数初始化
void init(unsigned int length)
{
	
	// 分配内存
	cudaMalloc((void **)&dev_A, size);
	cudaMalloc((void **)&dev_B, size);
	cudaMalloc((void **)&dev_C, size);

	// 拷贝内存
	cudaMemcpy(dev_A, A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_B, B, size, cudaMemcpyHostToDevice);

}
