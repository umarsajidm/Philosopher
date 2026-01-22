#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data{

    int no_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int no_of_times_each_philo_must_eat;
    int someone_die;
}   t_data;

typedef struct s_philo{
    pthread_t       tid;
    int             id;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_mutex_t *right_mutex;
    pthread_mutex_t *left_mutex;
    struct s_data   *data;
}      t_philo;



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

void init_data(t_philo *philos, t_data *data)
{
    // Write the loop here
    // Assign ID
    // Assign Left Fork pointer
    // Assign Right Fork pointer (Use the % formula!)
    // Assign data pointer
}


void init_philos(t_philo *philo, t_data *data)
{
    int i = 0;
    while (data->no_of_philo > 0)
    {
        philo->id == i++;
        philo->left_mutex == fork[i];
        philo->right_mutex == fork[(i + 1) % data->no_of_philo];
        philo->s_data = data;
    }
}


int main(int ac, char **av)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    long long millisecond = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec/1000;

    ft_usleep(millisecond);

    return 0;
}