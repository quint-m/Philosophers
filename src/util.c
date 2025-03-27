/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:27 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 17:05:13 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf(RED"Usage: ./philo <number_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n"RESET);
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("Illegal character found near %c\n", argv[i][j]);
				return (0);
			}
			j++;
		}
	}
	return (1);
}

long	ft_atol(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i])
	{
		result *= 10;
		result += (s[i] - '0');
		i++;
	}
	return (result);
}

/**
 * Get time in milliseconds
 */
int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
	{
		printf(RED"gettime error\n"RESET);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	info(t_philosopher *philo, char *msg)
{
	int	time;

	pthread_mutex_lock(philo->log_mutex);
	time = get_time();
	if (!philosopher_check_dead(philo))
		printf("%i %i %s\n", (time - philo->start_time),
			philo->p_num, msg);
	pthread_mutex_unlock(philo->log_mutex);
}

/**
 * Sleep for u_sec milliseconds
 */
int	acc_usleep(size_t m_sec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < m_sec)
		usleep(250);
	return (0);
}
