#include "A_add_B.h"

int main(void)
{
	//���鸳��ֵ
	for(int i=0;i<N;i++)
	{
		A[i]=1;
		B[i]=1;
	}

	//��ʼCPU����
	start_CPU = clock();
	for(int i=0;i<N;i++)
	{
		C[i]=A[i]+B[i];
	}
	finish_CPU = clock();

	//��ʼ��GPU����Ĳ���
	init(N);
	
	//��ʼGPU����
	start_GPU = clock();
	//*vector_add(A,B,N);
	//ִ�к˺���
	AaddB<<<num_blocks, threadsPerBlock>>>(dev_A, dev_B, dev_C, N);
	finish_GPU = clock();
printf("C[10]=%10f      \n",C[0]);

	// �����������
	cudaMemcpy(C , dev_C, size, cudaMemcpyDeviceToHost);

	//�ͷ��ڴ�
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);

	//�������鿴
	for(int i=0;i<N;i++)
	{
		//printf("A=%f   %d\n",A[i],i );
		//printf("B=%f   %d\n",B[i],i );
		//printf("%f+%f=%f   %d\n",A[i],B[i],C[i],i );
	}
	printf("\n");
	//��ʾ�̺߳��߳̿������
	printf("threadsPerBlock =%d\n",threadsPerBlock  );
	printf("num_blocks=%d\n",num_blocks);
	printf("\n");
	//��ʾGPU����ʱ
	time_GPU = (double)(finish_GPU - start_GPU)*1000 ;
	printf( "time_GPU=%f us\n", time_GPU);
	printf("\n");
	//��ʾCPU����ʱ
	time_CPU = (double)(finish_CPU - start_CPU)*1000 ;
	printf( "time_CPU=%f us\n", time_CPU);

	return 0;
}