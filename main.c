#include "philo.h"

void	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]))
			return ;
		i++;
	}
	pthread_mutex_lock(&data->dead_lock);
	data->start_time = gettimeoftheday();
	i = 0;
	while (i < data->no_of_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		philo[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	data->simulation_ready = 1;
	pthread_mutex_unlock(&data->dead_lock);
	monitor(philo);
	i = -1;
	while (++i < data->no_of_philo)
		pthread_join(philo[i].tid, NULL);
}

void	cleanup_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
		pthread_mutex_destroy(&data->fork[i++]);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->fork);
	free(philo);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("data allocation failed\n"), 1);
	init_data(data, ac, av);
	if (!data->fork)
		return (free(data), 1);
	philo = malloc(sizeof(t_philo) * data->no_of_philo);
	if (!philo)
		return (free(data->fork), free(data), 1);
	init_philos(philo, data);
	start_simulation(data, philo);
	cleanup_philo(data, philo);
	return (0);
}