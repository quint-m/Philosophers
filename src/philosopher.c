/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:19 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/25 18:38:19 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_create(t_philosopher *philos, pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		philos[i].p_num = i + 1;
		philos[i].is_dead = &(program->died);
		philos[i].num_philos = program->num_philos;
		philos[i].log_mutex = &(program->log_mutex);
		philos[i].eat_mutex = &(program->eat_mutex);
		philos[i].dead_mutex = &(program->dead_mutex);
		philos[i].sync_mutex = &(program->sync_mutex);
		philos[i].meal_count = 0;
		philos[i].start_time = get_time();
		philos[i].last_meal = philos[i].start_time;
		philos[i].tte = program->time_to_eat;
		philos[i].ttd = program->time_to_die;
		philos[i].tts = program->time_to_sleep;
		philos[i].l_fork = &forks[i];
		philos[i].program = program;
		if (i > 0)
			philos[i].r_fork = &forks[i - 1];
		else
			philos[i].r_fork = &forks[program->num_philos - i - 1];
		if (program->num_philos == 1)
			philos[i].r_fork = NULL;
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
	pthread_mutex_lock(philo->log_mutex);
	philo->start_time = get_time();
	pthread_mutex_unlock(philo->log_mutex);
	if (philo->p_num % 2 == 0)
		acc_usleep(1);
	pthread_mutex_lock(philo->sync_mutex);
	pthread_mutex_unlock(philo->sync_mutex);
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
	pthread_mutex_lock(program->philosophers[i].eat_mutex);
	if (program->meal_count < 0)
		return (pthread_mutex_unlock(&(program->eat_mutex)), 0);
	philo = &(program->philosophers[0]);
	while (i < program->num_philos)
	{
		if (program->philosophers[i].meal_count < philo->meal_count)
			philo = &(program->philosophers[i]);
		i++;
		
	}
	if (philo->meal_count >= program->meal_count)
	{
		pthread_mutex_lock(&(program->dead_mutex));
		program->died = 1;
		pthread_mutex_unlock(&(program->dead_mutex));
	}
	pthread_mutex_unlock(&(program->eat_mutex));
	return (philo->meal_count >= program->meal_count);
}

int	philosopher_has_starved(t_program *program)
{
	int				i;
	int				diff;
	t_philosopher	philo;

	i = 0;
	diff = 0;
	while (i < program->num_philos)
	{
		// philo = program->philosophers[i];
		pthread_mutex_lock(&program->eat_mutex);
		diff = get_time() - program->philosophers[i].last_meal;
		pthread_mutex_unlock(&program->eat_mutex); // Unlock the program's eat_mutex before returning
		if (diff >= program->time_to_die)
		{
            info(&program->philosophers[i], "died");
            pthread_mutex_lock(&program->dead_mutex);
            *(program->philosophers[i].is_dead) = 1;
            pthread_mutex_unlock(&program->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
