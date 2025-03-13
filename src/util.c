/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:27 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/13 18:30:24 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
	{
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = 1;
	while (argv[i])
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
		i++;
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

int	get_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
	{
		//TODO:Handle it
		printf("ERROR\n");
	}
	return (tv.tv_sec * 1000);
}

void	info(t_philosopher *philo, char *msg)
{
	int	time;

	pthread_mutex_lock(philo->log_mutex);
	time = get_time();
	printf("%i %i %s\n", (time - philo->start), philo->p_num, msg);
	pthread_mutex_unlock(philo->log_mutex);
}
