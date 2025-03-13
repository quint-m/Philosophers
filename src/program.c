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
#include <pthread.h>

void	program_create(char **args, t_program *program)
{
	program->num_philos = ft_atol(args[1]);
	program->time_to_die = ft_atol(args[2]);
	program->time_to_eat = ft_atol(args[3]);
	program->time_to_sleep = ft_atol(args[4]);

	pthread_mutex_init(&(program->log_mutex), NULL);
}

void	program_destroy(t_program *program)
{
	pthread_mutex_destroy(&(program->log_mutex));
}
