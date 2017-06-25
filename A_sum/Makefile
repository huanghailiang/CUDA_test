ALL:

	nvcc --compiler-options -fPIC -c A_sum.cu -lcudart -I"/usr/local/cuda/include/"

	nvcc --compiler-options -fPIC -o A_sum A_sum.o  -lcudart -I"/usr/local/cuda/include/" -L"/usr/local/cuda/lib64"


	rm -f A_sum.o 
