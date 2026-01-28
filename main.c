#include "philo.h"

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
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
    pthread_mutex_init(&data->write_lock, NULL);
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
        philo[i].data = data;
        philo[i].id = i + 1;
        philo[i].last_meal_time = data->start_time;
        philo[i].meals_eaten = 0;
        if (philo[i].data->no_of_philo % 2 == 0)
        {
            philo[i].right_mutex = &data->fork[(i + 1) % data->no_of_philo];
            philo[i].left_mutex = &data->fork[i];
        }
        else
        {
            philo[i].left_mutex = &data->fork[i];
            philo[i].right_mutex = &data->fork[(i + 1) % data->no_of_philo];
        }        
        i++;
    }
}

void print_action(t_philo *philo, char *str)
{
    long long time;

    time = gettimeoftheday() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->write_lock);
    printf("%lld %i %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->data->write_lock);
}

void time_to_eat(t_data *data, t_philo *philo)
{
    // int i = 0;
    
    while (1)
    {
        pthread_mutex_lock(&philo->data->dead_lock);
        if (data->someone_die == 1)
        {
            pthread_mutex_unlock(&philo->data->dead_lock);
            break;
        }
        pthread_mutex_unlock(&philo->data->dead_lock);

        pthread_mutex_lock(philo->left_mutex);
        print_action(philo, "philo is taking a fork");
        
        pthread_mutex_lock(philo->right_mutex);
        print_action(philo, "philo is eating");

        pthread_mutex_lock(&philo->data->meal_lock);
        philo->last_meal_time = gettimeoftheday();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->data->meal_lock);
        

        ft_usleep(data->time_to_eat);
        
        pthread_mutex_unlock(philo->left_mutex);
        pthread_mutex_unlock(philo->right_mutex);
        print_action(philo, "philo is sleeping");
        
        ft_usleep(data->time_to_sleep);

        print_action(philo, "philo is thinking");
    }
}

void *thread_routine_funtion(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->data->no_of_philo == 1)
    {
        pthread_mutex_lock(philo->left_mutex);
        print_action(philo, "has taken a fork");
        ft_usleep(philo->data->time_to_die); 
        pthread_mutex_unlock(philo->left_mutex);
        return NULL;
    }

    if (philo->id % 2 == 0)
        ft_usleep(1);
    time_to_eat(philo->data, philo);
    return NULL;
}
int check_if_all_ate(t_philo *philo)
{
    int i;
    int finished_eating;

    i = 0;
    finished_eating = 0;
    if (philo->data->no_of_times_each_philo_must_eat == -1)
        return (0);
    while (i < philo->data->no_of_philo)
    {
        pthread_mutex_lock(&philo->data->meal_lock);
        if (philo[i].meals_eaten >= philo->data->no_of_times_each_philo_must_eat)
            finished_eating++;
        pthread_mutex_unlock(&philo->data->meal_lock);
        i++;
    }
    if (finished_eating == philo->data->no_of_philo)
    {
        pthread_mutex_lock(&philo->data->dead_lock);
        philo->data->someone_die = 1;
        pthread_mutex_unlock(&philo->data->dead_lock);
        return (1);
    }
    return (0);
}


void monitor(t_philo *philo)
{
    long long time_since_last_meal;
    long long time;
    int i;

    time = gettimeoftheday() - philo->data->start_time;
    while(1)
        {
            i = 0;
            while (i < philo->data->no_of_philo)
            {
                pthread_mutex_lock(&philo->data->dead_lock);
                if (philo->data->someone_die == 1)
                {
                    pthread_mutex_unlock(&philo->data->dead_lock);
                    return ;
                }
                pthread_mutex_unlock(&philo->data->dead_lock);
                
                pthread_mutex_lock(&philo->data->meal_lock);
                time_since_last_meal = gettimeoftheday() - philo[i].last_meal_time;
                pthread_mutex_unlock(&philo->data->meal_lock);

                if (time_since_last_meal > philo[i].data->time_to_die)
                {
                    pthread_mutex_lock(&philo[i].data->dead_lock);
                    time = gettimeoftheday() - philo->data->start_time;
                    philo[i].data->someone_die = 1;
                    printf("%lld %i philo died\n", time, philo[i].id);
                    pthread_mutex_unlock(&philo[i].data->dead_lock);
                    return ;
                }
                i++;
            }
            if (check_if_all_ate(philo) == 1)
                return ;
            //usleep(500);
        }
    return;
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
            return(printf("threading failed "), 1);
        if (data->someone_die == 1)
            break ;
        i++;
    }
    monitor(philo);
    i = 0;
    while(data->no_of_philo > i)
    {
        pthread_join(philo[i++].tid, NULL);
    }
    pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->meal_lock);
    pthread_mutex_destroy(&data->write_lock);
    return 0;
}