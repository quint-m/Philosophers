/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:04:57 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/25 17:32:15 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	p_sleep(t_philosopher *philo)
{
	info(philo, "is sleeping");
	acc_usleep(philo->tts);
}

void	p_eat(t_philosopher *philo)
{
	int	side;
	if (philo->r_fork == NULL || philo->l_fork == NULL)
	{
		acc_usleep(philo->ttd);
		return ;
	}
	// Make sure we prevent deadlock by not always taking right fork first
	if (philo->p_num % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		info(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		info(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
	}
	info(philo, "is eating");
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(philo->eat_mutex);
	acc_usleep(philo->tte);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	p_think(t_philosopher *philo)
{
	if (philosopher_check_dead(philo))
		return ;
	info(philo, "is thinking");
	acc_usleep((philo->ttd - philo->tte - philo->tts) / 5);
}
