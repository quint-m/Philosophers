/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:19 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/13 18:43:30 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_create(t_philosopher *philos, pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		philos[i].p_num = i;
		philos[i].num_philos = program->num_philos;
		philos[i].log_mutex = &program->log_mutex;
		philos[i].eat_mutex = &program->eat_mutex;
		philos[i].meal_count = 0;
		philos[i].start = get_time();
		philos[i].tte = program->time_to_eat * 1000;
		philos[i].ttd = program->time_to_die * 1000;
		philos[i].tts = program->time_to_sleep * 1000;
		philos[i].l_fork = &forks[i];
		if (i > 0)
			philos[i].r_fork = &forks[i - 1];
		else
			philos[i].r_fork = &forks[program->num_philos - i];
		i++;
	}
}

void	*philosopher_routine(void *param)
{
	t_philosopher *philo;

	philo = (t_philosopher*) param;
	if (philo->p_num % 2 == 0)
		usleep(1);
	while (1)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (0);
}

int	philosopher_count_meals(t_program *program)
{
	int	i;

	i = 0;
	if (program->eat_count < 0)
		return (0);
	while (i < program->num_philos)
	{
		pthread_mutex_lock(program->philosophers[i].eat_mutex);
		if (! (program->philosophers[i].meal_count >= 7))
		{
			pthread_mutex_unlock(&(program->eat_mutex));
			break ;
		}
		pthread_mutex_unlock(program->philosophers[i].eat_mutex);
		i++;
	}
	return (i == program->num_philos);
}
