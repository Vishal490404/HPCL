#include<stdio.h>
#include<omp.h>
using namespace std;

int main(){
    int num_operations = 100000000;
    double a = 1.1, b = 2.2, c = 0.0; 
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:c)
    for (long long int i = 0; i < num_operations; i++) {
        c += a * b; 
    }
    end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    long long int total_flops = num_operations * 2; 
    double flops = total_flops / time_taken;

    printf("Time taken: %f seconds\n", time_taken);
    printf("FLOPs: %0.2f\n", flops);
    printf("GFLOPs: %0.2f\n", flops / 1e9);
    return 0;
}