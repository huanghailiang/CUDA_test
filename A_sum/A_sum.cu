#include "A_sum.h"

int main()
{
	//���鸳ֵ
	for(int i=0;i<N;i++)
	{
		A[i]=i+1;
	}

	//��ʼCPU����
	start_CPU = clock();
	for(int i=0;i<N;i++)
	{
		sum+=i+1;
	}
	finish_CPU = clock();

	//�ڴ�ȳ�ʼ��
	init (N);

	//��ʼGPU����
	start_GPU = clock();

	//square_sum_array(A,N);
	A_sum<<<num_blocks, threads_per_block, threads_per_block*sizeof(float)>>>(sum_a, dsum_per_block, N);
	//����GPU�ڴ浽CPU�ڴ�
	cudaMemcpy(sum_per_block, dsum_per_block, (num_blocks+1)*sizeof(float), cudaMemcpyDeviceToHost);
	  for( int i=0; i<num_blocks; i++ )
	{
		//printf("sum_per_block=%f  %d\n",sum_per_block[i],i);
		sum_all+=sum_per_block[i];
	}

	finish_GPU = clock();
	//�ͷ��ڴ�
	cudaFree(dsum_per_block);
	cudaFree(sum_a);
	free(sum_per_block);

	printf("\n");
	
	//�������鿴
	printf ("GPU:sum_all=%f\n",sum_all);
	printf ("CPU:sum=%f\n",(float)sum);	

	//��ʾ�̺߳��߳̿������
	//printf("threadsPerBlock =%d\n",threadsPerBlock  );
	//printf("num_blocks=%d\n",num_blocks);
	printf("\n");
	//��ʾGPU����ʱ
	time_GPU = (double)(finish_GPU - start_GPU)*1000 ;
	printf( "time_GPU=%f us\n", time_GPU);	
	//��ʾCPU����ʱ
	time_CPU = (double)(finish_CPU - start_CPU)*1000 ;
	printf( "time_CPU=%f us\n", time_CPU);
	printf("\n");

	return 0;
}