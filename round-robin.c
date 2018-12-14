#include <stdio.h>
#include "round-robin.h"

int main(int argc, char const *argv[]){
	task TASKLIST[25];
	queuehead = queuetail = 0;
	int timer = 0;
	int finished_task_number = 0;
	int num_of_tasks;
	int qtime;
	int counter;

	// input
	printf("## Scheduler of Round-Robin method\ninput:\n");
	scanf("%d", &num_of_tasks);
	for(int i = 0; i < num_of_tasks; ++i)
	{
		scanf(" %s %d %d",
			TASKLIST[i].name, &TASKLIST[i].arrival_time, &TASKLIST[i].cost);
		TASKLIST[i].progress = 0;
		TASKLIST[i].status = 0;
	}
	scanf(" %d", &qtime);

	// sort TASKLIST arrival order with b_sort
	for(int i = 0; i < num_of_tasks; ++i)
	{
		for(int j = 0; j < num_of_tasks; ++j)
		{
			if (TASKLIST[i].arrival_time < TASKLIST[j].arrival_time)
			{
				task tmp = TASKLIST[i];
				TASKLIST[i] = TASKLIST[j];
				TASKLIST[j] = tmp;
			}
		}
	}
	enqueue(&TASKLIST[0]);
	TASKLIST[0].status = 1;

	// Output
	printf("\nOutput:\nstart\n");
	while(finished_task_number != num_of_tasks)
	{
		finished_task_number = 0;
		task *current_job = dequeue();
		if(current_job == NULL)
		{
			++timer;
			for (int i = 0; i < num_of_tasks; ++i)
			{
				if(TASKLIST[i].status == 2)
					++finished_task_number;
			}
			if(finished_task_number != num_of_tasks)
			{
				for(int i = 0; i < num_of_tasks; ++i)
				{
					if(TASKLIST[i].arrival_time <= timer && !TASKLIST[i].status)
					{
						enqueue(&TASKLIST[i]);
						TASKLIST[i].status = 1;
					}
				}
				continue;
			}
			else{
				printf("Error\n");
				return -1;
			}
		}

		counter = timer + qtime;
		if(current_job->cost - current_job->progress <= qtime)
		{
			counter = timer + current_job->cost - current_job->progress;
		}
		while(timer < counter)
		{
			++timer;
			++current_job->progress;
			if(current_job->cost == current_job->progress)
			{
				current_job->status = 2;
				printf("%2d Task:%s is finish\n", timer, current_job->name);
				current_job->fin_time = timer;
			}
			else printf("%2d Task:%s\n", timer, current_job->name);
			for(int i = 0; i < num_of_tasks; ++i)
			{
				if(TASKLIST[i].arrival_time == timer && !TASKLIST[i].status)
				{
					enqueue(&TASKLIST[i]);
					TASKLIST[i].status = 1;
				}
			}
		}
		for (int i = 0; i < num_of_tasks; ++i)
		{
			if(TASKLIST[i].status == 2)	++finished_task_number;
		}
		if(current_job->status == 1)	enqueue(current_job);
	}
	printf("end\n\n");
	print_result(TASKLIST, num_of_tasks);
	return 0;
}

