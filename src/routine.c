/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:04:57 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/18 19:24:58 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	pick_fork(t_philosopher *philo)
{
	if (philo->p_num % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
}

void	p_sleep(t_philosopher *philo)
{
	philo->state = SLEEPING;
	info(philo, "is sleeping");
	usleep(philo->tts);
}

void	p_eat(t_philosopher *philo)
{
	int	side;
	// Make sure we prevent deadlock by not always taking right fork first
	side = pick_fork(philo);
	info(philo, "has taken a fork");
	if (side > 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	philo->state = EATING;
	info(philo, "is eating");
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(philo->eat_mutex);
	usleep(philo->tte);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	p_think(t_philosopher *philo)
{
	philo->state = THINKING;
	info(philo, "is thinking");
}
