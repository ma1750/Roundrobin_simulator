
/*
    C-lang Header for Round-Robin system.
        by ma1750 (github.com/ma1750) & HerpMR (github.com/HerpMR)
*/

#include <stdio.h>

static int queuehead;
static int queuetail;

typedef struct{
    char name[10];
    int arrival_time;
    int cost;
    int progress;
    int fin_time;
    int status;
} task;

/*
    Discription of (*task).status:
        0: Not in queue
        1: In queue
        2: Done
*/

static task* queue[5000];

// enqueue task's pointer
void enqueue(task *x){
    queuetail = (queuetail + 1) % 5000;
    queue[queuetail] = x;
    if(queuehead == queuetail){
        printf("Error: Overflow\n");
        return;
    }
}

// dequeue task's pointer
task* dequeue(void){
    if(queuehead == queuetail)  return NULL;
    queuehead = (queuehead + 1) % 5000;
    return queue[queuehead];
}

// display executing result
void print_result(task *task_list, int tasks){
    int sum = 0;
    printf("  TaskName|  ArrivalTime|  FinishTime|\n");
    for(int i = 0; i < tasks; ++i){
        printf("  %8s|  %11d|  %10d|\n",
            task_list[i].name, task_list[i].arrival_time, task_list[i].fin_time);
        sum += task_list[i].fin_time - task_list[i].arrival_time;
    }
    printf("\nAverage_Process_Time = %.2f\n", (double)sum/tasks);
}

