#include <stdio.h>
#include <omp.h>
#include <vector>

using namespace std;

float calculate_pi(int terms, int thread)
{
    float PI = 3;
    omp_set_num_threads(thread);
    #pragma omp parallel for reduction(+:PI)
    for (int i = 0; i < terms; i++)
    {
        int n = 2 + 2 * i;
        int sign = (i % 2 == 0) ? 1 : -1;
        PI += (4.0 / ((n) * (n + 1) * (n + 2))) * sign;
    }
    return PI;
}
int main()
{
    FILE *fp = fopen("ps_2.csv", "w");

    if (fp == NULL)
    {
        printf("File not found");
        return 1;
    }

    vector<int> terms = {10, 100, 1000, 1500, 2000};
    fprintf(fp, "%s,%s,%s,%s\n", "NumberOfTerms", "Threads", "Time(s)", "Value of PI");
    // #pragma omp parallel for
    for (int i = 0; i < terms.size(); i++)
    {
        for (int thread = 1; thread <= 8; thread++)
        {
            auto start = omp_get_wtime();
            float PI = calculate_pi(terms[i], thread);
            auto end = omp_get_wtime();
            auto time = end - start;

            fprintf(fp, "%d,%d,%.8f,%.15f\n", terms[i], thread, time, PI);
        }
    }
    fclose(fp);
    return 0;
}