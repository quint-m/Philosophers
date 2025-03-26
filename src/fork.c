/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:20:22 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 15:43:42 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_create(pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
		pthread_mutex_init(&(forks[i++]), NULL);
}

void	forks_destroy(pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
		pthread_mutex_destroy(&(forks[i++]));
}
