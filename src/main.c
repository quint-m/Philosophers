/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:19:47 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/26 16:59:10 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	on_error(t_program *p, pthread_mutex_t *f)
{
	write(2, RED"An error occurred during philo execution\n"RESET, 41);
	program_destroy(p);
	forks_destroy(f, p);
}

int	main(int argc, char **argv)
{
	t_philosopher	philos[MAX_PHILO];
	t_program		program;
	pthread_mutex_t	forks[MAX_PHILO];
	int				num_philos;
	int				err;

	err = 0;
	if (!validate_input(argc, argv))
		return (1);
	err += program_create(argv, &program);
	err += forks_create(forks, &program);
	philos_create(philos, forks, &program);
	program.philosophers = philos;
	err += threads_create(philos, &program);
	if (err > 0)
	{
		on_error(&program, forks);
		return (1);
	}
	threads_start(philos, &program);
	forks_destroy(forks, &program);
	program_destroy(&program);
	return (0);
}
