//��ʱ��������
#include "time.h"
clock_t start_GPU, finish_GPU,start_CPU, finish_CPU; 
double time_GPU,time_CPU;

#include "stdio.h"

float sum_all = 0;//һ���������  GPU
int sum=0;//һ���������   CPU
#define N 10000 //�����С
float A[N];//��������
//�����߳̿�Ĵ�С�Լ��߳̿�ĸ���
const int  threads_per_block = 1024;//�߳̿�Ĵ�С��Ŀǰ��Щgpu���߳̿����Ϊ512����ЩΪ1024.
const int  num_blocks = (N / threads_per_block) + ((N% threads_per_block) ? 1 : 0);
//GPU��͸�����ĺ��Լ�CPU�ϵĴ洢
float *sum_per_block;
float *sum_a, *dsum_per_block;

//��ʼ���ڴ����
void init (int length)
{
	//����CPU�ڴ�
	sum_per_block=(float*)malloc((num_blocks+1)*sizeof(float));
	//����GPU�ڴ�
	cudaMalloc((void **)&sum_a, length*sizeof(float));
	cudaMalloc((void **)&dsum_per_block, (num_blocks+1)*sizeof(float));
	//����CPU�ڴ浽GPU�ڴ�
	cudaMemcpy( sum_a, A, length*sizeof(float), cudaMemcpyHostToDevice );
}

