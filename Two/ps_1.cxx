#include <stdio.h>
#include <omp.h>
#include <vector>
//#include <chrono>

using namespace std;
//using namespace std::chrono;

int main(){
    FILE *fp = fopen("ps_1.csv", "w");

    if (fp == NULL){
        printf("File not found");
        return 1;
    }

    fprintf(fp, "Datasize,Threads,Time\n");

    printf("%-12s %-7s %s\n", "DataSize", "Threads", "Time(s)");

    vector<int> N = {/*100000, removed because time precision is bad*/ 1000000, 10000000, 100000000};


    for(int i = 0; i < N.size(); i++){
        vector<float> vec(N[i]), ans(N[i]);
        for(int ele = 1; ele <= N[i]; ele++){
            vec[ele-1] = ele * 1.005;
        }

        for(int thread = 1; thread <= 8; thread++){
            //auto begin = high_resolution_clock::now();
            auto start = omp_get_wtime();
            omp_set_num_threads(thread);
            #pragma omp parallel for
            for(int j = 0; j < N[i]; j++){
                ans[j] = vec[j] + 9.3;
            }
            auto end = omp_get_wtime();
            //auto finish = high_resolution_clock::now();
            auto time = end - start;
            // auto time2 = duration_cast<duration<double>>(finish - begin).count();
            printf("%-12d %-7d %.8f\n", N[i], thread, time/*, time2*/);
            fprintf(fp, "%d,%d,%.8f\n", N[i], thread, time/*, time2*/);
        }


    }
    fclose(fp);
}



