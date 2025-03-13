/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:22:43 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/13 18:35:57 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	threads_create(t_philosopher *philos, t_program *program)
{
	int	i;
	int	t_result;

	i = 0;
	while (i < program->num_philos)
	{
		t_result = pthread_create(&(philos[i].thread), NULL, philosopher_routine, (void *)&philos[i]);
		if (t_result != 0)
		{
			//TODO: Check
			printf("Failed initializing philo threads\n");
		}
		i++;
	}
	pthread_create(&((*program).thread), NULL, program_monitor, program);
}

void	threads_start(t_philosopher *philos, t_program *program)
{
	int	i;

	pthread_join((*program).thread, NULL);
	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
