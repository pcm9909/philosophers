#include "thread.h"

void *func(void *arg)
{
	int i = *(int *)arg;

	printf("thread %d\n", i);
}

int main()
{
	pthread_t thread;

	int i = 0;
	while(i < 10)
	{
		pthread_create(&thread, NULL, &func, (void *)&i);
		pthread_detach(thread);
		i++;
	}
}
// int main()
// {
// 	pthread_t thread;

// 	int i = 0;
// 	while(i < 10)
// 	{
// 		pthread_create(&thread, NULL, &func, (void *)&i);
// 		pthread_join(thread,NULL);
// 		i++;
// 	}
// }