#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int ft_atoi(const char *str);

typedef struct s_data{

    int             no_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             no_of_times_each_philo_must_eat;
    int             someone_die;
    long long       start_time;
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
    data->start_time = gettimeoftheday();
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
        philo[i].id = i + 1;
        philo[i].left_mutex = &data->fork[i];
        philo[i].right_mutex = &data->fork[(i + 1) % data->no_of_philo];
        philo[i].data = data;
        i++;
    }
}

void time_to_eat(t_data *data, t_philo *philo)
{
    int i = 0;
    long long time;

    time = gettimeoftheday() - data->start_time;
    while (1)
    {
        if (pthread_mutex_lock(philo->left_mutex) != 0)
        {
            printf("locking failed");
               return ;
        }

        printf("%lld %i philo has taken the fork\n", gettimeoftheday() - data->start_time, philo->id);
        
        if (pthread_mutex_lock(philo->right_mutex) != 0)
        {
            printf("locking failed");
            return ;
        }

        printf("%lld %i philo is eating\n", gettimeoftheday() - data->start_time,  philo->id);
        philo->last_meal_time = gettimeoftheday();
        ft_usleep(data->time_to_eat);
        
        if (pthread_mutex_unlock(philo->left_mutex) != 0)
        {
            printf("locking failed");
            return ;
        }
        if (pthread_mutex_unlock(philo->right_mutex) != 0)
        {
            printf("locking failed");
            return ;
        }
        
        printf("%lld %i philo is sleeping\n", gettimeoftheday() - data->start_time,  philo->id);
        
        ft_usleep(data->time_to_sleep);

        printf("%lld %i philo is thinking\n", gettimeoftheday() - data->start_time,  philo->id);
    }
}

void *thread_routine_funtion(void *arg)
{
    t_philo *my_philo_data;
    
    if (my_philo_data->id % 2 == 0)
        ft_usleep(1);

    my_philo_data = (t_philo *)arg;
    time_to_eat(my_philo_data->data, my_philo_data);
    return NULL;
}

int main(int ac, char **av)
{
    t_data  *data;
    t_philo *philo;
    int     i = 0;

    data = malloc(sizeof(t_data));
    if (!data)
        return(printf("data allocation failed"), 1);
    init_data(data, ac, av);
    philo =  malloc(sizeof(t_philo) * data->no_of_philo);
    if (!philo)
        return(printf("philo allocation failed"));
    init_philos(philo, data);
    while (data->no_of_philo > i)
    {
        if (pthread_create(&philo[i].tid, NULL, thread_routine_funtion, &philo[i]))
            return(printf("threading failed"), 1);
        i++;
    }
    i = 0;
    while(data->no_of_philo > i)
    {
        pthread_join(philo[i++].tid, NULL);
    }
    return 0;
}