ALL:

	nvcc --compiler-options -fPIC -c a_add_b.cu -lcudart -I"/usr/local/cuda/include/"

	nvcc --compiler-options -fPIC -o a_add_b a_add_b.o -lcudart -I"/usr/local/cuda/include/" -L"/usr/local/cuda/lib64"

	rm -f a_add_b.o
