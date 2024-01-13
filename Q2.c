#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sched.h>

struct timespec return_endtimer(){
    struct timespec endtime;
    if(clock_gettime(CLOCK_REALTIME, &endtime) == -1){
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    else{
        return endtime;
    }
}

int check_process_end(int pid){
    int status;

    if(waitpid(pid, &status, 0) == -1){
        perror("waitpid");
        exit(EXIT_FAILURE);
        return -1;
    }

    if(WIFEXITED(status)){
        return 1;
    }

    else{
        return 0;
    }
}

int main(){

    int parent_pid = getpid();

    int core_id = 0; 
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(core_id, &cpu_set);
    if (sched_setaffinity(parent_pid, sizeof(cpu_set_t), &cpu_set) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }
    
    int fifo_process_pid = -1;
    int rr_process_pid = -1;
    int other_process_pid = -1;

    struct sched_param parameter;

    struct timespec starttime;
    if(clock_gettime(CLOCK_REALTIME, &starttime) == -1){
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    // printf("PID of parent process is %d\n", getpid());
    int rc = 0;

    for(int i = 0; i<3; i++){
        if(getpid() == parent_pid){
            rc = fork();
            if(rc<0){
                printf("fork failed");
            }

            else if(rc == 0){
                if(i==0){
                    // printf("PID of child process is %d i %d\n", getpid(), i);
                    other_process_pid = getpid();
                }

                else if(i==1){
                    // printf("PID of child process is %d i %d\n", getpid(), i);
                    rr_process_pid = getpid();

                }

                else if(i==2){
                    // printf("PID of child process is %d i %d\n", getpid(), i);
                    fifo_process_pid = getpid();
                }
            }

            else if(rc > 0){
                if(i==0){
                    other_process_pid = rc;
                }

                else if(i==1){
                    rr_process_pid = rc;
                }

                else if(i==2){
                    fifo_process_pid = rc;
                }
            }
        }
    }

    if(getpid() == fifo_process_pid){
        // printf("This is FIFO process\n");
        parameter.sched_priority = 50;

        if(sched_setscheduler(0, SCHED_FIFO, &parameter) == -1){
            perror("sched_setscheduler FIFO");
            exit(EXIT_FAILURE);
        }
    }

    else if(getpid() == rr_process_pid){
        // printf("This is RR process\n");
        parameter.sched_priority = 50;

        if(sched_setscheduler(0, SCHED_RR, &parameter) == -1){
            perror("sched_setscheduler RR");
            exit(EXIT_FAILURE);
        }
    }

    else if(getpid() == other_process_pid){
        // printf("This is OTHER process \n");

        // if(sched_setscheduler(0, SCHED_OTHER, &parameter) == -1){
        //     perror("sched_setscheduler OTHER");
        //     exit(EXIT_FAILURE);
        // }
    }

    if(getpid() != parent_pid){
        if(execl("./Counting", "./Counting", NULL) == -1){
        perror("execl");
        exit(EXIT_FAILURE);
        }
    }

    int flag1 = 1; int flag2 = 1; int flag3 = 1;
    double elapsedtime_fifo; double elapsedtime_rr; double elapsedtime_other;
    struct timespec endtime_fifo; struct timespec endtime_rr; struct timespec endtime_other;
    
    while(flag1||flag2||flag3){
        if(flag1 == 1 && check_process_end(fifo_process_pid) == 1){
            endtime_fifo = return_endtimer();
            elapsedtime_fifo = difftime(endtime_fifo.tv_sec, starttime.tv_sec) + (endtime_fifo.tv_nsec - starttime.tv_nsec)/1e9;
            flag1 = 0;
        }

        if(flag2 == 1 && check_process_end(rr_process_pid) == 1){
            endtime_rr = return_endtimer();
            elapsedtime_rr = difftime(endtime_rr.tv_sec, starttime.tv_sec) + (endtime_rr.tv_nsec - starttime.tv_nsec)/1e9;
            flag2 = 0;
        }

        if(flag3 == 1 && check_process_end(other_process_pid) == 1){
            endtime_other = return_endtimer();
            elapsedtime_other = difftime(endtime_other.tv_sec, starttime.tv_sec) + (endtime_other.tv_nsec - starttime.tv_nsec)/1e9;
            flag3 = 0;
        }
    }

    printf("Time taken by FIFO: %f seconds\n", elapsedtime_fifo);
    printf("Time taken by RR: %f seconds\n", elapsedtime_rr);
    printf("Time taken by OTHER: %f seconds\n", elapsedtime_other);

    FILE *file = fopen("Data.txt", "w");

    if(file == NULL){
        printf("Unable to open file\n");
        return 1;
    }

    double time_values[] = {elapsedtime_fifo, elapsedtime_rr, elapsedtime_other};
    char* policy_labels[]= {"FIFO", "RR", "OTHER"};

    for(int i = 0; i<3; i++){
        fprintf(file, "%s %f\n", policy_labels[i], time_values[i]);
    }

    fclose(file);

    return 0;
}