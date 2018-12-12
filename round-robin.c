#include <stdio.h>
#include "round-robin.h"

void Enqueue(task*);
task* Dequeue();
void print_result(task*, int);

int main()
{
	task task_list[TASK_COUNT];
	queuehead = queuetail = 0;
	int timer = 0;
	int finished_task_number = 0;
	int num_of_tasks;
	int step;

	//input
	printf("input : Task_Number\n");
	scanf("%d", &num_of_tasks);
	printf("input : Step_Number\n");
	scanf("%d", &step);
	printf("input : Task_Name Arrival_Time Cost\n");
	for(int i = 0; i < num_of_tasks; ++i)
	{
		scanf(" %s %d %d", task_list[i].name, &task_list[i].arrival_time, &task_list[i].cost);
		task_list[i].progress = 0;
		task_list[i].status = 0;
	}

	//sort task_list arrival order
	//bubble sort is not so good
	for(int i = 0; i < num_of_tasks; ++i)
		for(int j = 0; j < num_of_tasks; ++j)
		{
			if (task_list[i].arrival_time < task_list[j].arrival_time)
			{
				task tmp = task_list[i];
				task_list[i] = task_list[j];
				task_list[j] = tmp;
			}
		}

	Enqueue(&task_list[0]);
	task_list[0].status = 1;

	//main process
	printf("\nstart\n");
	while(finished_task_number != num_of_tasks)
	{
		finished_task_number = 0;
		task *current_job = Dequeue();
		if(current_job == NULL)
		{
			++timer;
			for (int i = 0; i < num_of_tasks; ++i)
			{
				if(task_list[i].status == 2)
					++finished_task_number;
			}
			if(finished_task_number != num_of_tasks)
			{
				for(int i = 0; i < num_of_tasks; ++i)
				{
					if(task_list[i].arrival_time <= timer && task_list[i].status == 0)
					{
						Enqueue(&task_list[i]);
						task_list[i].status = 1;
					}
				}
				continue;
			}
			else
			{
				printf("Eroor\n");
				return -1;
			}
		}

		int counter = timer + step;
		if(current_job->cost - current_job->progress <= step)
			counter = timer + current_job->cost - current_job->progress;
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
			else
			{
				printf("%2d Task:%s\n", timer, current_job->name);
			}
			for(int i = 0; i < num_of_tasks; ++i)
			{
				if(task_list[i].arrival_time == timer && task_list[i].status == 0)
				{
					Enqueue(&task_list[i]);
					task_list[i].status = 1;
				}
			}
		}
		for (int i = 0; i < num_of_tasks; ++i)
		{
			if(task_list[i].status == 2)
				++finished_task_number;
		}
		if(current_job->status == 1)
			Enqueue(current_job);
	}
	printf("end\n\n");
	print_result(task_list, num_of_tasks);
	return 0;
}
