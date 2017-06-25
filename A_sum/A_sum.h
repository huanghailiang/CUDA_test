#include "memcpy.h"

//һ���������
__global__ void A_sum(float *A,float *dsum_per_block, const unsigned int length)
{
	extern __shared__ float cache[];//���빲���ڴ�
	unsigned int tid = threadIdx.x+blockIdx.x*blockDim.x;
	unsigned int cacheid=threadIdx.x;

	float temp = 0;
	while(tid<length)
	{
		temp+=A[tid];
		tid+=blockDim.x*gridDim.x;//��������
	}
	cache[cacheid]=temp;
		__syncthreads();
  
	//����ÿ���߳̿��ж�Ӧ������cache������ÿ���̵߳ļ�����

	int i=blockDim.x/2;
	while(i!=0)
	{
	if(cacheid<i){ cache[cacheid]+= cache[cacheid+i]; }
	__syncthreads();
	i/= 2;
	}
	if (cacheid == 0)
	{ 
		dsum_per_block[blockIdx.x] = cache[0];
	}
}

//һ���������
float square_sum_array(float *A, int length)
{
	//sum_all=0;
  //const int  threads_per_block = 1024;
  //�߳̿�Ĵ�С��Ŀǰ��Щgpu���߳̿����Ϊ512����ЩΪ1024.
  //const int  num_blocks = (length / threads_per_block) + ((length% threads_per_block) ? 1 : 0);
  //65536
  //float *sum_per_block;
  //float *sum_a, *dsum_per_block;
  //����CPU�ڴ�
  //sum_per_block=(float*)malloc((num_blocks+1)*sizeof(float));
  //����GPU�ڴ�
  //cudaMalloc((void **)&sum_a, length*sizeof(float));
  //cudaMalloc((void **)&dsum_per_block, (num_blocks+1)*sizeof(float));
  //����CPU�ڴ浽GPU�ڴ�
  //cudaMemcpy( sum_a, A, length*sizeof(float), cudaMemcpyHostToDevice );


  //A_sum<<<num_blocks, threads_per_block, threads_per_block*sizeof(float)>>>(sum_a, dsum_per_block, length);
 //����GPU�ڴ浽CPU�ڴ�
  //cudaMemcpy(sum_per_block, dsum_per_block, (num_blocks+1)*sizeof(float), cudaMemcpyDeviceToHost);

  
	//for( int i=0; i<num_blocks; i++ )
	//{
	//	printf("sum_per_block=%f  %d\n",sum_per_block[i],i);
	//	sum_all+=sum_per_block[i];
	//}
  
	cudaFree(dsum_per_block);
	cudaFree(sum_a);

	free(sum_per_block);

	return sum_all;
  

  

}