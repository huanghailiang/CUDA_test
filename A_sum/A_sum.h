#include "memcpy.h"

//一个数组求和
__global__ void A_sum(float *A,float *dsum_per_block, const unsigned int length)
{
	extern __shared__ float cache[];//申请共享内存
	unsigned int tid = threadIdx.x+blockIdx.x*blockDim.x;
	unsigned int cacheid=threadIdx.x;

	float temp = 0;
	while(tid<length)
	{
		temp+=A[tid];
		tid+=blockDim.x*gridDim.x;//更新索引
	}
	cache[cacheid]=temp;
		__syncthreads();
  
	//这样每个线程块中对应的数组cache保存了每个线程的计算结果

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

//一个数组求和
float square_sum_array(float *A, int length)
{
	//sum_all=0;
  //const int  threads_per_block = 1024;
  //线程块的大小。目前有些gpu的线程块最大为512，有些为1024.
  //const int  num_blocks = (length / threads_per_block) + ((length% threads_per_block) ? 1 : 0);
  //65536
  //float *sum_per_block;
  //float *sum_a, *dsum_per_block;
  //分配CPU内存
  //sum_per_block=(float*)malloc((num_blocks+1)*sizeof(float));
  //分配GPU内存
  //cudaMalloc((void **)&sum_a, length*sizeof(float));
  //cudaMalloc((void **)&dsum_per_block, (num_blocks+1)*sizeof(float));
  //拷贝CPU内存到GPU内存
  //cudaMemcpy( sum_a, A, length*sizeof(float), cudaMemcpyHostToDevice );


  //A_sum<<<num_blocks, threads_per_block, threads_per_block*sizeof(float)>>>(sum_a, dsum_per_block, length);
 //拷贝GPU内存到CPU内存
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