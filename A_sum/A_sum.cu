#include "A_sum.h"

int main()
{
	//数组赋值
	for(int i=0;i<N;i++)
	{
		A[i]=i+1;
	}

	//开始CPU计算
	start_CPU = clock();
	for(int i=0;i<N;i++)
	{
		sum+=i+1;
	}
	finish_CPU = clock();

	//内存等初始化
	init (N);

	//开始GPU计算
	start_GPU = clock();

	//square_sum_array(A,N);
	A_sum<<<num_blocks, threads_per_block, threads_per_block*sizeof(float)>>>(sum_a, dsum_per_block, N);
	//拷贝GPU内存到CPU内存
	cudaMemcpy(sum_per_block, dsum_per_block, (num_blocks+1)*sizeof(float), cudaMemcpyDeviceToHost);
	  for( int i=0; i<num_blocks; i++ )
	{
		//printf("sum_per_block=%f  %d\n",sum_per_block[i],i);
		sum_all+=sum_per_block[i];
	}

	finish_GPU = clock();
	//释放内存
	cudaFree(dsum_per_block);
	cudaFree(sum_a);
	free(sum_per_block);

	printf("\n");
	
	//输出结果查看
	printf ("GPU:sum_all=%f\n",sum_all);
	printf ("CPU:sum=%f\n",(float)sum);	

	//显示线程和线程块的数量
	//printf("threadsPerBlock =%d\n",threadsPerBlock  );
	//printf("num_blocks=%d\n",num_blocks);
	printf("\n");
	//显示GPU的用时
	time_GPU = (double)(finish_GPU - start_GPU)*1000 ;
	printf( "time_GPU=%f us\n", time_GPU);	
	//显示CPU的用时
	time_CPU = (double)(finish_CPU - start_CPU)*1000 ;
	printf( "time_CPU=%f us\n", time_CPU);
	printf("\n");

	return 0;
}