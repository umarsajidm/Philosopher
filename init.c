#include "philo.h"

void	init_data(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->no_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->no_of_times_each_philo_must_eat = -1;
	if (ac == 6)
		data->no_of_times_each_philo_must_eat = ft_atoi(av[5]);
	data->someone_die = 0;
	data->simulation_ready = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->no_of_philo);
	if (!data->fork)
		return ;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	while (i < data->no_of_philo)
		pthread_mutex_init(&data->fork[i++], NULL);
}

void	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		if (i % 2 == 0)
		{
			philo[i].left_mutex = &data->fork[i];
			philo[i].right_mutex = &data->fork[(i + 1) % data->no_of_philo];
		}
		else
		{
			philo[i].left_mutex = &data->fork[(i + 1) % data->no_of_philo];
			philo[i].right_mutex = &data->fork[i];
		}
		i++;
	}
}