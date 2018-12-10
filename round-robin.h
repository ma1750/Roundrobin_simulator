#define Q_SIZE 10000
#define TASK_COUNT 100
static int queuehead;
static int queuetail;

typedef struct{
    char name[10];
    int arrival_time;
    int cost;
    int progress;
    int fin_time;
    int status;/*0:not into queue 1:in queue 2:finished execute*/
} task;

static task* queue[Q_SIZE];

void Enqueue(task *x)
{
    queuetail = (queuetail+1)%Q_SIZE;
    queue[queuetail] = x;
    if(queuehead == queuetail)
    {
        printf("Eroor: Overflow\n");
        return;
    }
}

task* Dequeue()
{
    if(queuehead == queuetail)
        return NULL;
    queuehead = (queuehead+1)%Q_SIZE;
    return queue[queuehead];
}

void print_result(task *task_list, int tasks)
{
    int sum = 0;
    printf("Task_Name|Arrival_Time|Finish_Time|\n");
    for(int i = 0; i < tasks; ++i)
    {
        printf("\t%s|\t%d|\t%d|\n", task_list[i].name, task_list[i].arrival_time, task_list[i].fin_time);
        sum += (task_list[i].fin_time - task_list[i].arrival_time);
    }
    printf("\nAverage_Process_Time = %.2f\n", (double)sum/tasks);
}