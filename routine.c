#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->someone_die == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	time = gettimeoftheday() - philo->data->start_time;
	printf("%lld %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	check_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->someone_die == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_mutex);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_mutex);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = gettimeoftheday();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
}

void	time_to_eat(t_data *data, t_philo *philo)
{
	while (1)
	{
		if (check_dead_flag(data))
			break ;
		philo_eats(philo);
		if (check_dead_flag(data))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(data->time_to_sleep);
		print_action(philo, "is thinking");
		if (data->no_of_philo % 2 != 0)
			ft_usleep(2);
		else
			ft_usleep(1);
	}
}

void	*thread_routine_funtion(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->no_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_mutex);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(20);
	time_to_eat(philo->data, philo);
	return (NULL);
}