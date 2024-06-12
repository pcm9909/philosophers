#include "thread.h"

//경쟁 조건 :  두 개 이상의 스레드가 공유 데이터에 액세스할 수 있고 동시에 변경하려고 할 때 발생함
int cnt = 0;

void *routine()
{
	int i = 0;
	while(i++ < 100000)
	{
		cnt++;
	}
	return (void *)0;
}

int main()
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, &routine, NULL);
	pthread_create(&thread2, NULL, &routine, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("cnt = %d\n", cnt);
	return 0;
}