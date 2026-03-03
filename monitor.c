#include "philo.h"

int	check_philo_death(t_philo *philo, int i)
{
	long long	time_since_meal;
	long long	time;

	pthread_mutex_lock(&philo->data->meal_lock);
	time_since_meal = gettimeoftheday() - philo[i].last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (time_since_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		time = gettimeoftheday() - philo->data->start_time;
		printf("%lld %i died\n", time, philo[i].id);
		pthread_mutex_unlock(&philo->data->write_lock);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->someone_die = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_philo *philo)
{
	int	i;
	int	finished_eating;

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

void	monitor(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (check_dead_flag(philo->data))
			return ;
		while (i < philo->data->no_of_philo)
		{
			if (check_philo_death(philo, i))
				return ;
			i++;
		}
		if (check_all_ate(philo))
			return ;
		usleep(1000);
	}
}