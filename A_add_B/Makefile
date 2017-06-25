ALL:

	nvcc --compiler-options -fPIC -c A_add_B.cu -lcudart -I"/usr/local/cuda/include/"

	nvcc --compiler-options -fPIC -o A_add_B A_add_B.o -lcudart -I"/usr/local/cuda/include/" -L"/usr/local/cuda/lib64"

	rm -f A_add_B.o
