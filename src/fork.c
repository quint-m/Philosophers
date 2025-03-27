/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:20:22 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 16:54:45 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_create(pthread_mutex_t *forks, t_program *program)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (i < program->num_philos)
		e += pthread_mutex_init(&(forks[i++]), NULL);
	return (e);
}

void	forks_destroy(pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
		pthread_mutex_destroy(&(forks[i++]));
}
