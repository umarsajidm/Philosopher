#ifndef PHILO_H
#define PHILO_H

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
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
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

int	ft_atoi(const char *str);
long long gettimeoftheday(void);
void ft_usleep(long long time_in_ms);
void init_data(t_data *data, int ac, char **av);
void init_philos(t_philo *philo, t_data *data);
void print_action(t_philo *philo, char *str);
void time_to_eat(t_data *data, t_philo *philo);
void *thread_routine_funtion(void *arg);
void monitor(t_philo *philo);
int main(int ac, char **av);


#endif
