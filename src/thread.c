/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:22:43 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 16:55:29 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_philosopher *philos, t_program *program)
{
	int	i;
	int	err;
	int	t_result;

	i = 0;
	err = 0;
	pthread_mutex_lock(&(program->sync_mutex));
	while (i < program->num_philos)
	{
		err += pthread_create(&(philos[i].thread), NULL,
				philosopher_routine, (void *)&philos[i]);
		if (err != 0)
			return (err);
		i++;
	}
	err += pthread_create(&((*program).thread), NULL, program_monitor, program);
	pthread_mutex_unlock(&(program->sync_mutex));
	return (err);
}

void	threads_start(t_philosopher *philos, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join((*program).thread, NULL);
}
