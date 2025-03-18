/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:19 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/18 18:41:22 by qmennen          ###   ########.fr       */
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
		philos[i].is_dead = &(program->died);
		philos[i].num_philos = program->num_philos;
		philos[i].log_mutex = &(program->log_mutex);
		philos[i].eat_mutex = &(program->eat_mutex);
		philos[i].dead_mutex = &(program->dead_mutex);
		philos[i].meal_count = 0;
		philos[i].start_time = get_time();
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

int	philosopher_check_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->is_dead))
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);		
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);	
}

void	*philosopher_routine(void *param)
{
	t_philosopher *philo;

	philo = (t_philosopher*) param;
	// Sync the start by creating a mutex on the program (start_mutex)
	// Now before we enter routine, we lock and unlock this mutex (which wo't be possible because the program has locked it and only unlocks it when all threads have joined)
	if (philo->p_num % 2 == 0)
		usleep(1);
	while (!philosopher_check_dead(philo))
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (0);
}

int	philosopher_count_meals(t_program *program)
{
	int				i;
	int				meal_count;
	t_philosopher	*philo;

	i = 0;
	meal_count = 0;
	if (program->meal_count < 0)
		return (0);
	philo = &(program->philosophers[0]);
	while (i < program->num_philos - 1)
	{
		pthread_mutex_lock(program->philosophers[i].eat_mutex);
		if (program->philosophers[i].meal_count < philo->meal_count)
			philo = &(program->philosophers[i]);		
		i++;
		pthread_mutex_unlock(&(program->eat_mutex));
	}
	if (philo->meal_count >= program->meal_count)
	{
		pthread_mutex_lock(&(program->dead_mutex));
		program->died = 1;
		pthread_mutex_unlock(&(program->dead_mutex));
	}
	return (philo->meal_count >= program->meal_count);
}
