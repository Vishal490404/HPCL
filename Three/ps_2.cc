#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>

using namespace std;

void createRandomMatrixOfSize(vector<vector<int>> &mat1, vector<vector<int>> &mat2, int size)
{
    mat1.assign(size, vector<int>(size));
    mat2.assign(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            mat1[i][j] = (rand() % 100);
            mat2[i][j] = (rand() % 100);
        }
    }
}
int main()
{

    FILE *fp = fopen("ps_2.csv", "w");

    fprintf(fp, "%s,%s,%s\n", "Threads", "Size", "Time(s)");
    vector<vector<int>> mat1, mat2, mat3;
    vector<int> sizes = {250, 500, 750, 1000, 2000}, threads = {1, 2, 4, 8};

    for (auto &thread : threads)
    {
        omp_set_num_threads(thread);
        for (auto &size : sizes)
        {
            createRandomMatrixOfSize(mat1, mat2, size);
            mat3.assign(size, vector<int>(size));
            auto start = omp_get_wtime();
            #pragma omp parallel for collapse(2)
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    mat3[i][j] = mat1[i][j] + mat2[i][j];
                }
            }

            auto end = omp_get_wtime();
            auto time = end - start;
            fprintf(fp, "%d,%d,%.8f\n", thread, size, time);
        }
    }
    fclose(fp);
}