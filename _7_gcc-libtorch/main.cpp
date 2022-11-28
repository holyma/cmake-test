// #include <stdio.h>
#include <iostream>
#include <torch/script.h>

int main(void)
{
	// printf("hello world\n");
	torch::Tensor tensor = torch::rand({2, 3});
	std::cout << tensor << std::endl;
	
	return 0;

}

/*

g++  /root/git/tmp/gcc-test/main.cpp -std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0 \
 -L /mnt/f/sublinux/pkg/libtorch-shared-with-deps-1.12.1+cpu/libtorch/lib \
 -ltorch_cpu -lc10
*/