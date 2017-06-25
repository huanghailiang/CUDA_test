#include "A_add_B.h"

int main(void)
{
	//数组赋初值
	for(int i=0;i<N;i++)
	{
		A[i]=1;
		B[i]=1;
	}

	//开始CPU计算
	start_CPU = clock();
	for(int i=0;i<N;i++)
	{
		C[i]=A[i]+B[i];
	}
	finish_CPU = clock();

	//初始化GPU计算的参数
	init(N);
	
	//开始GPU计算
	start_GPU = clock();
	//*vector_add(A,B,N);
	//执行核函数
	AaddB<<<num_blocks, threadsPerBlock>>>(dev_A, dev_B, dev_C, N);
	finish_GPU = clock();
printf("C[10]=%10f      \n",C[0]);

	// 结果拷贝回来
	cudaMemcpy(C , dev_C, size, cudaMemcpyDeviceToHost);

	//释放内存
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);

	//输出结果查看
	for(int i=0;i<N;i++)
	{
		//printf("A=%f   %d\n",A[i],i );
		//printf("B=%f   %d\n",B[i],i );
		//printf("%f+%f=%f   %d\n",A[i],B[i],C[i],i );
	}
	printf("\n");
	//显示线程和线程块的数量
	printf("threadsPerBlock =%d\n",threadsPerBlock  );
	printf("num_blocks=%d\n",num_blocks);
	printf("\n");
	//显示GPU的用时
	time_GPU = (double)(finish_GPU - start_GPU)*1000 ;
	printf( "time_GPU=%f us\n", time_GPU);
	printf("\n");
	//显示CPU的用时
	time_CPU = (double)(finish_CPU - start_CPU)*1000 ;
	printf( "time_CPU=%f us\n", time_CPU);

	return 0;
}