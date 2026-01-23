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
    pthread_mutex_t *fork;
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

void init_data(t_data *data, int ac, char **av)
{
    int i = 0;
    data->no_of_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->no_of_times_each_philo_must_eat = -1;
    if (ac == 6)
        data->no_of_times_each_philo_must_eat = ft_atoi(av[5]);
    data->someone_die = 0;
    data->fork = malloc(sizeof(pthread_mutex_t)*data->no_of_philo);
    if (!data->fork)
        return ;
    while (i < data->no_of_philo)
    {
        pthread_mutex_init(&data->fork[i], NULL);
        i++;
    }
}
void init_philos(t_philo *philo, t_data *data)
{
    int i = 0;
    while (i < data->no_of_philo)
    {
        philo[i]->id = i++;
        philo[i]->left_mutex = data->fork[i];
        philo[i]->right_mutex = data->fork[(i + 1) % data->no_of_philo];
        philo[i]->s_data = data;
    }
}


int main(int ac, char **av)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    ft_usleep(600);

    return 0;
}