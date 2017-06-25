//计时参数定义
#include "time.h"
clock_t start_GPU, finish_GPU,start_CPU, finish_CPU; 
double time_GPU,time_CPU;

#include "stdio.h"

float sum_all = 0;//一个数组求和  GPU
int sum=0;//一个数组求和   CPU
#define N 10000 //数组大小
float A[N];//定义数组
//设置线程块的大小以及线程块的个数
const int  threads_per_block = 1024;//线程块的大小。目前有些gpu的线程块最大为512，有些为1024.
const int  num_blocks = (N / threads_per_block) + ((N% threads_per_block) ? 1 : 0);
//GPU求和各个块的和以及CPU上的存储
float *sum_per_block;
float *sum_a, *dsum_per_block;

//初始化内存分配
void init (int length)
{
	//分配CPU内存
	sum_per_block=(float*)malloc((num_blocks+1)*sizeof(float));
	//分配GPU内存
	cudaMalloc((void **)&sum_a, length*sizeof(float));
	cudaMalloc((void **)&dsum_per_block, (num_blocks+1)*sizeof(float));
	//拷贝CPU内存到GPU内存
	cudaMemcpy( sum_a, A, length*sizeof(float), cudaMemcpyHostToDevice );
}

