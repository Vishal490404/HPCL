#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

#define VECTOR_SIZE 1000000
#define SCALAR 10

vector<int> getRandomVector(int size)
{
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    return arr;
}

void vector_scalar_add_static(const vector<int> &vec, vector<int> &result, int chunk, int threads)
{
    #pragma omp parallel for schedule(static, chunk) num_threads(threads)
    for (int i = 0; i < vec.size(); i++) {
        result[i] = vec[i] + SCALAR;
    }
}

void vector_scalar_add_dynamic(const vector<int> &vec, vector<int> &result, int chunk, int threads)
{
    #pragma omp parallel for schedule(dynamic, chunk) num_threads(threads)
    for (int i = 0; i < vec.size(); i++) {
        result[i] = vec[i] + SCALAR;
    }
}

void nowait_demo(const vector<int> &vec, vector<int> &res1, vector<int> &res2, int threads)
{
    int size = vec.size();
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for nowait
        for (int i = 0; i < size / 2; i++)
            res1[i] = vec[i] + 1;

        #pragma omp for
        for (int i = size / 2; i < size; i++)
            res2[i] = vec[i] + 2;
    }
}

int main()
{
    vector<int> chunk_sizes = {1, 5, 10, 20, 50};
    vector<int> thread_counts = {1, 2, 4, 8};

    vector<int> vec = getRandomVector(VECTOR_SIZE);
    vector<int> res_static(VECTOR_SIZE);
    vector<int> res_dynamic(VECTOR_SIZE);
    vector<int> res1(VECTOR_SIZE, 0);
    vector<int> res2(VECTOR_SIZE, 0);

    FILE *fs = fopen("PS_3_Static.csv", "w");
    FILE *fd = fopen("PS_3_Dynamic.csv", "w");
    fprintf(fs, "Chunk_Size,Threads,Time(s)\n");
    fprintf(fd, "Chunk_Size,Threads,Time(s)\n");

    for (auto &chunk : chunk_sizes) {
        for (auto &threads : thread_counts) {
            double start = omp_get_wtime();
            vector_scalar_add_static(vec, res_static, chunk, threads);
            double end = omp_get_wtime();
            double elapsed = end - start;
            fprintf(fs, "%d,%d,%.6f\n", chunk, threads, elapsed);
        }
    }

    for (auto &chunk : chunk_sizes) {
        for (auto &threads : thread_counts) {
            double start = omp_get_wtime();
            vector_scalar_add_dynamic(vec, res_dynamic, chunk, threads);
            double end = omp_get_wtime();
            double elapsed = end - start;
            fprintf(fd, "%d,%d,%.6f\n", chunk, threads, elapsed);
        }
    }

    fclose(fs);
    fclose(fd);

    nowait_demo(vec, res1, res2, 4);

    return 0;
}