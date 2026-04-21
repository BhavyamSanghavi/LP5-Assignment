#include <iostream>
using namespace std;

__global__ void add(int *a, int *b, int *c) {
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

int main() {
    int a[5] = {1,2,3,4,5};
    int b[5] = {5,4,3,2,1};
    int c[5];

    int *d_a, *d_b, *d_c;

    cudaMalloc(&d_a, 5*sizeof(int));
    cudaMalloc(&d_b, 5*sizeof(int));
    cudaMalloc(&d_c, 5*sizeof(int));

    cudaMemcpy(d_a, a, 5*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, 5*sizeof(int), cudaMemcpyHostToDevice);

    add<<<1,5>>>(d_a, d_b, d_c);

    cudaMemcpy(c, d_c, 5*sizeof(int), cudaMemcpyDeviceToHost);

    for(int i=0;i<5;i++)
        cout << c[i] << " ";

    return 0;
}


#define N 3   // change size here

__global__ void multiply(int *A, int *B, int *C) {
    int row = threadIdx.y;
    int col = threadIdx.x;

    int sum = 0;
    for(int k = 0; k < N; k++) {
        sum += A[row*N + k] * B[k*N + col];
    }

    C[row*N + col] = sum;
}

int main() {
    int A[N*N] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    int B[N*N] = {
        9,8,1,
        6,5,4,
        3,2,1
    };

    int C[N*N];

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, N*N*sizeof(int));
    cudaMalloc(&d_B, N*N*sizeof(int));
    cudaMalloc(&d_C, N*N*sizeof(int));

    cudaMemcpy(d_A, A, N*N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N*N*sizeof(int), cudaMemcpyHostToDevice);

    multiply<<<1, N*N>>>(d_A, d_B, d_C);

    cudaMemcpy(C, d_C, N*N*sizeof(int), cudaMemcpyDeviceToHost);

    // Print result
    for(int i = 0; i < N*N; i++) {
        cout << C[i] << " ";
        if((i+1)%N == 0) cout << endl;
    }

    return 0;
}