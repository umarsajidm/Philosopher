// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utilities.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mumar <mumar@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/01 00:00:00 by mumar             #+#    #+#             */
// /*   Updated: 2026/03/01 00:00:00 by mumar            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	sum *= sign;
	return (sum);
}

long long	gettimeoftheday(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (time_in_ms);
}

void	ft_usleep(long long time_in_ms)
{
	long long	starttime;

	starttime = gettimeoftheday();
	while ((gettimeoftheday() - starttime) < time_in_ms)
	{
		usleep(500);
	}
}
