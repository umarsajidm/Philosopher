/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:27:18 by musajid           #+#    #+#             */
/*   Updated: 2026/03/09 10:27:18 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	wait_for_gate(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->simulation_ready == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(500);
	}
}

void	philo_think(t_data *data, t_philo *philo)
{
	print_action(philo, "is thinking");
	if (data->no_of_philo % 2 != 0)
		usleep(1000);
}

void	time_to_eat(t_data *data, t_philo *philo)
{
	while (!check_dead_flag(data))
	{
		pthread_mutex_lock(philo->left_mutex);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_mutex);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		pthread_mutex_lock(&data->meal_lock);
		philo->last_meal_time = gettimeoftheday();
		philo->meals_eaten++;
		pthread_mutex_unlock(&data->meal_lock);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(philo->right_mutex);
		if (check_dead_flag(data))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(data->time_to_sleep);
		philo_think(data, philo);
	}
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_gate(philo);
	if (philo->data->no_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_mutex);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	time_to_eat(philo->data, philo);
	return (NULL);
}
