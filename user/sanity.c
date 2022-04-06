#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

//Fibonacci sequence
int fib(int n) {
    if (n <= 1) {
        return 1;
    }
    return fib(n-1) + fib(n-2);
}
//Use this for long computation
//fib(35) takes roughly 30 secs
void longComputation(){
    fib(35);
}

int main(int argc, char *argv[]) {

    int ctime, ttime, retime, rutime, stime;
    int retime_ave = 0;
    int rutime_ave = 0;
    int stime_ave = 0;
    int turnaround_ave = 0;
    
    for(int i = 0; i < 20; i++) {
        
        int pid = fork();
        if (pid < 0) { /* error occurred */
            printf(1, "Fork failed!");
        }
        if(pid == 0) { /* child process */
            longComputation();
            exit();
        }
    }
    /* parent process */
    for(int i = 0; i < 20; i++) { 
        int pid = wait_stat(&ctime, &ttime, &retime, &rutime, &stime);
        retime_ave += retime;
        rutime_ave += rutime;
        stime_ave += stime;
        turnaround_ave += ttime - ctime;
        printf(1, "PID[%d] Creation[%d] Termination[%d] Ready Time[%d] Running Time[%d] Sleep Time[%d]\n", 
        pid, ctime, ttime, retime, rutime, stime);
    }
    
    retime_ave /= 20;
    rutime_ave /= 20;
    stime_ave /= 20;
    turnaround_ave/= 20;
    printf(1, "Average Wait Time[%d] Average Running Time[%d] Average Sleep Time[%d] Average Turnaround Time[%d]\n",
    retime_ave, rutime_ave, stime_ave, turnaround_ave);
    exit();
}