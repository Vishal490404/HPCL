#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> getRandomArray(int size)
{
    vector<int> arr;
    for (int i = 0; i < size; i++)
    {
        arr.push_back(rand() % 100);
    }
    return arr;
}

int main()
{
    vector<int> A = getRandomArray(10000), B = getRandomArray(10000);
    long long result = 0;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());
    auto start = omp_get_wtime();
    #pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < A.size(); i++)
    {
        result += A[i] * B[i];
    }
    auto end = omp_get_wtime();
    auto time = end - start;
    cout << "Time Elapsed: " << time << endl;

    return 0;
}