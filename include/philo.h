/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:07:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/31 15:10:48 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define USLEEP_DELAY 100

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	int				meal_count;
	int				number;
	int				is_ready_to_quit;
	long int		last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	eating_mutex;
};

struct s_data
{
	int				finish;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_must_eat;
	pthread_t		handler_thread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
};

#endif
