#include "thread.h"

void *self()
{
	printf("pid = %lu\n" ,pthread_self());
}

int main()
{
	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, self,NULL);
	pthread_create(&tid2, NULL, self,NULL);
	pthread_create(&tid3, NULL, self,NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	printf("main pid = %lu\n" ,pthread_self());
}