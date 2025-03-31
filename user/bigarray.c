#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define ARR_SIZE (1 << 16)  // 2^16
#define N 4    // number of children
 
static int arr[ARR_SIZE];

int
main(int argc, char *argv[])
{
    //  build an array of 2^16 integers with consecutive numbers from 0 to 65535
    
    for(int i = 0; i < ARR_SIZE; i++){
        arr[i] = i;
    }

    int pids[N];
    int res = forkn(N, pids);

    if(res == 0){
        int status[N];
        int n_ptr[1];  
        waitall(n_ptr, status);

        // print child PIDs
        for(int i = 0; i < N; i++){
            printf("child %d pid: %d\n", i+1, pids[i]);
        }

        // print children exit statuses
        for(int i = 0; i < N; i++){
            printf("child %d calculated sum: %d\n", i+1, status[i]);
        }

        // compute sum of children statuses
        int total_sum = 0;
        for(int i = 0; i < N; i++){
            total_sum += status[i];
        }
        printf("Total sum of child statuses: %d\n", total_sum);
    }
    else { //childs

        int chunk = ARR_SIZE / N;
        int start = (res - 1) * chunk;
        int end = (res == N) ? ARR_SIZE : start + chunk; 

        int sum = 0;
        for(int i = start; i < end; i++){
            sum += arr[i];
        }

        // exit with status = sum
        exit(sum, "");
    }

    // only the parent eventually reaches here
    exit(0, "");
}
