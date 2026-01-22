#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

long long gettimeoftheday(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long time_in_ms = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec/1000;
    return (time_in_ms);
}

void ft_usleep(long long time_in_ms)
{
    struct timeval tv;

    long long starttime =gettimeoftheday();

    long long currenttime = gettimeoftheday();

    while ((currenttime - starttime) < time_in_ms)
    {
        usleep(500);
        currenttime = gettimeoftheday();
    }
    printf("executed");
}



int main(int ac, char **av)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    long long millisecond = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec/1000;

    ft_usleep(millisecond);

    return 0;
}