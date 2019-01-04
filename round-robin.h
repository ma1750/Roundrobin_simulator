#define Q_SIZE 10000
#define TASK_COUNT 100

typedef struct {
	char name[10];
	int arrival_time;
	int cost;
	int progress;
	int fin_time;
	int status;
	/*
	 *0:not into queue
	 *1:in queue
	 *2:finished execute
	 */
} task_t;

static int queuehead;
static int queuetail;
static task_t* queue[Q_SIZE];

void enqueue(task_t *x)
{
	queuetail = (queuetail+1) % Q_SIZE;
	queue[queuetail] = x;
	if (queuehead == queuetail) {
		printf("Eroor: Overflow\n");
		return;
	}
}

task_t* dequeue()
{
	if (queuehead == queuetail)
		return NULL;
	queuehead = (queuehead + 1) % Q_SIZE;
	return queue[queuehead];
}

void print_result(task_t *task_list, int tasks)
{
	int sum = 0;
	printf("Task_Name|Arrival_Time|Finish_Time|\n");
	for (int i = 0; i < tasks; ++i) {
		printf("%9s|%12d|%11d|\n",
			task_list[i].name, task_list[i].arrival_time,
			task_list[i].fin_time);
		sum += task_list[i].fin_time - task_list[i].arrival_time;
	}
	printf("\nAverage_Process_Time = %.2f\n", (double)sum/tasks);
}

void fetch_new_task(task_t *task_list, int num_of_tasks, int time)
{
	for (int i = 0; i < num_of_tasks; ++i) {
		if(task_list[i].arrival_time <= time
				&& !task_list[i].status) {
			enqueue(&task_list[i]);
			task_list[i].status = 1;
		}
	}
}