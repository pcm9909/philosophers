#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
int main()
{
    struct timeval startTime, currentTime;
    int diffTime = 0;

    gettimeofday(&startTime, NULL);

    while(1)
    {
        usleep(1000);
        gettimeofday(&currentTime, NULL);

        diffTime = (int)(currentTime.tv_sec - startTime.tv_sec) * 1000 + (currentTime.tv_usec - startTime.tv_usec) / 1000;
        printf("%llu ms\n", diffTime);
    }
    return 0;
}
