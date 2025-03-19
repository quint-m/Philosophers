/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:20:49 by qmennen           #+#    #+#             */
/*   Updated: 2025/03/18 19:55:08 by qmennen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_PHILO 200
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef	enum s_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_philosopher
{
	int				p_num;
	int				num_philos;
	t_state			state;
	int				start_time;
	int				last_meal;
	int				meal_count;
	int				ttd;
	int				tte;
	int				tts;
	int				*is_dead;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*sync_mutex;
	struct s_program	*program;
}	t_philosopher;

typedef struct s_program
{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meal_count;
	int				died;
	t_philosopher	*philosophers;
	pthread_t		thread;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	sync_mutex;	
}	t_program;

void	*program_monitor(void *param);
void	forks_create(pthread_mutex_t *forks, t_program *program);
void	forks_destroy(pthread_mutex_t *forks, t_program *program);
void	program_create(char **args, t_program *program);
void	program_destroy(t_program *program);
void	threads_create(t_philosopher *philos, t_program *program);
void	threads_start(t_philosopher *philos, t_program *program);
int		validate_input(int argc, char **argv);
/**
 *
 * Philosopher
 */
void	p_sleep(t_philosopher *philo);
void	p_think(t_philosopher *philo);
void	p_eat(t_philosopher *philo);
void	*philosopher_routine(void *param);
int		philosopher_check_dead(t_philosopher *philo);
void	philos_create(t_philosopher *philos, pthread_mutex_t *forks, t_program *program);
int		philosopher_count_meals(t_program *program);
int		philosopher_has_starved(t_program *program);
/**
 *
 * Utility
 */
long 	ft_atol(char *s);
int		get_time();
void	info(t_philosopher *philo, char *msg);
#endif
