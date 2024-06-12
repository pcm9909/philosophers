#include "thread.h"

//mutex
int cnt = 0;
pthread_mutex_t mutex;

void *routine()
{
	int i;

	i = 0;
	while(i++ < 10000)
	{
		pthread_mutex_lock(&mutex);
		cnt++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, &routine, NULL);
	pthread_create(&thread2, NULL, &routine, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("cnt = %d\n", cnt);

	return 0;
}