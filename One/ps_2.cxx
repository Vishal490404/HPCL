#include <stdio.h>
#include <omp.h>

using namespace std;

int main() {

    int num_of_threads;
    printf("Enter number of threads: ");
    scanf("%d", &num_of_threads);
    printf("====Sequential====\n");
    int thread_num = omp_get_thread_num();
    printf("Hello, World!, thread number %d\n", thread_num);
    printf("====Parallel====\n");
    omp_set_num_threads(num_of_threads);
    #pragma omp parallel
    {
        thread_num = omp_get_thread_num();
        printf("Hello, World!, thread number %d\n", thread_num);
    }
    
    return 0;
}