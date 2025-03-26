/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:19:47 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 15:51:11 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philosopher	philos[MAX_PHILO];
	t_program		program;
	pthread_mutex_t	forks[MAX_PHILO];
	int				num_philos;

	if (!validate_input(argc, argv))
		return (1);
	program_create(argv, &program);
	forks_create(forks, &program);
	philos_create(philos, forks, &program);
	program.philosophers = philos;
	threads_create(philos, &program);
	threads_start(philos, &program);
	forks_destroy(forks, &program);
	program_destroy(&program);
	return (0);
}
