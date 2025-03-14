/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:56:37 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/13 18:32:46 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*program_monitor(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	while (1)
	{
		if (philosopher_count_meals(program) == 1)
		{
			exit(0);
			break;
		}
	}
	return (0);
}

void	program_create(char **args, t_program *program)
{
	program->num_philos = ft_atol(args[1]);
	program->time_to_die = ft_atol(args[2]);
	program->time_to_eat = ft_atol(args[3]);
	program->time_to_sleep = ft_atol(args[4]);
	if (args[5])
		program->eat_count = ft_atol(args[5]);
	else
		program->eat_count = -1;

	pthread_mutex_init(&(program->log_mutex), NULL);
	pthread_mutex_init(&(program->eat_mutex), NULL);
}

void	program_destroy(t_program *program)
{
	pthread_mutex_destroy(&(program->log_mutex));
	pthread_mutex_destroy(&(program->eat_mutex));
}
