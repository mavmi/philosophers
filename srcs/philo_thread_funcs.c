/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 19:17:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/31 18:24:27 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_thread_funcs.h"

static void	print_message(t_philo *philo, char *msg)
{
	philo->is_ready_to_quit = 1;
	pthread_mutex_lock(&philo->data->print_mutex);
	print_msg(get_timestamp(NULL, &philo->data->start_time)
		* 1e-3, philo->number, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->is_ready_to_quit = 0;
}

static void	delay(t_philo *philo)
{
	long int		timestamp;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	timestamp = get_timestamp(&current_time, &philo->data->start_time) * 1e-3;
	if (philo->number % 2 == 0)
	{
		print_msg(timestamp, philo->number, IS_THINKING);
		my_sleep(philo->data->time_to_eat);
	}
	else if (philo->data->philo_count % 2 != 0
		&& philo->number == philo->data->philo_count)
	{
		print_msg(timestamp, philo->number, IS_THINKING);
		my_sleep(philo->data->time_to_eat * 2);
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_message(philo, GOT_FORK);
	philo->is_ready_to_quit = 1;
	pthread_mutex_lock(philo->second_fork);
	philo->is_ready_to_quit = 0;
	print_message(philo, GOT_FORK);
	pthread_mutex_lock(&philo->eating_mutex);
	philo->last_meal = get_timestamp(NULL, &philo->data->start_time) * 1e-3;
	pthread_mutex_unlock(&philo->eating_mutex);
	philo->meal_count++;
	print_message(philo, IS_EATING);
	my_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*philo_func(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	philo->last_meal = 0;
	philo->is_ready_to_quit = 1;
	delay(philo);
	while (!philo->data->finish)
	{
		eat(philo);
		print_message(philo, IS_SLEEPING);
		my_sleep(philo->data->time_to_sleep);
		print_message(philo, IS_THINKING);
		usleep(USLEEP_DELAY);
	}
	return (0);
}
