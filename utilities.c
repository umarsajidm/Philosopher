#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sum);
}

long long	gettimeoftheday(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// The stable Spinlock (No chunking, OS won't background this)
void	ft_usleep(long long time_in_ms)
{
	long long	start;

	start = gettimeoftheday();
	while ((gettimeoftheday() - start) < time_in_ms)
		usleep(500);
}

// Optimized: No double-locking bottleneck
void	print_action(t_philo *philo, char *str)
{
	long long	time;

	if (check_dead_flag(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_dead_flag(philo->data))
	{
		time = gettimeoftheday() - philo->data->start_time;
		printf("%lld %i %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}