/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:04:57 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/13 18:46:41 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	p_sleep(t_philosopher *philo)
{
	philo->state = SLEEPING;
	info(philo, "is sleeping");
	usleep(philo->tts);
}

void	p_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->l_fork);
	info(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	info(philo, "is eating");
	pthread_mutex_lock(philo->eat_mutex);
	philo->state = EATING;
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
