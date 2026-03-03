#include "philo.h"

int	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start_time = gettimeoftheday();
	while (i < data->no_of_philo)
	{
		philo[i].last_meal_time = data->start_time;
		if (pthread_create(&philo[i].tid, NULL,
				thread_routine_funtion, &philo[i]))
			return (printf("threading failed\n"), 1);
		i++;
	}
	monitor(philo);
	i = 0;
	while (i < data->no_of_philo)
		pthread_join(philo[i++].tid, NULL);
	return (0);
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
	philo = malloc(sizeof(t_philo) * data->no_of_philo);
	if (!philo)
		return (printf("philo allocation failed\n"), 1);
	init_philos(philo, data);
	start_simulation(data, philo);
	cleanup_philo(data, philo);
	return (0);
}