#include <iostream>
#include <stdio.h>

__global__ void kernel() {
    printf("Just a test! I am point cloud %d!\n", blockIdx.x);
}
int main() {
    kernel<<<9, 1>>>();
    cudaDeviceSynchronize(); ///wait for the kernel function to finish the execution, and then continue to execute the following code
    return 1;
}