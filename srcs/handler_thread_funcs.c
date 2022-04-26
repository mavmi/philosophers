/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_thread_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 19:50:16 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/31 15:55:26 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler_thread_funcs.h"

static int	is_dead(t_data *data, t_philo *philo)
{
	long int		time_diff;
	struct timeval	current_time;

	pthread_mutex_lock(&philo->eating_mutex);
	gettimeofday(&current_time, 0);
	time_diff = get_timestamp(&current_time, &data->start_time)
		* 1e-3 - philo->last_meal;
	pthread_mutex_unlock(&philo->eating_mutex);
	if (time_diff >= data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		print_msg(get_timestamp(&current_time, &data->start_time)
			* 1e-3, philo->number, DIED);
		return (1);
	}
	return (0);
}

static int	get_full_philos(t_data *data)
{
	int	philos_count;
	int	counter;

	if (data->each_must_eat == -1)
	{
		return (0);
	}
	philos_count = 0;
	counter = 0;
	while (counter < data->philo_count)
	{
		if (data->philos[counter].meal_count >= data->each_must_eat)
		{
			philos_count++;
		}
		counter++;
	}
	if (philos_count == data->philo_count)
		pthread_mutex_lock(&data->print_mutex);
	return (philos_count);
}

static void	wait_for_all(t_data *data)
{
	int	iter;
	int	ready_to_quit;

	iter = 0;
	ready_to_quit = 0;
	while (1)
	{
		if (data->philos[iter].is_ready_to_quit)
		{
			ready_to_quit++;
		}
		if (ready_to_quit == data->philo_count)
			return ;
		if (iter == data->philo_count - 1)
		{
			iter = 0;
			ready_to_quit = 0;
		}
		else
			iter++;
		usleep(USLEEP_DELAY);
	}
}

void	*handler_func(void *input)
{
	int		iter;
	int		full_philos;
	t_data	*data;

	full_philos = 0;
	data = (t_data *)input;
	while (1)
	{
		iter = 0;
		while (iter < data->philo_count)
		{
			if (is_dead(data, &data->philos[iter])
				|| get_full_philos(data) == data->philo_count)
			{
				data->finish = 1;
				wait_for_all(data);
				release_data(data, data->philo_count, data->philo_count, 1);
				return (NULL);
			}
			usleep(USLEEP_DELAY);
			iter++;
		}
	}
}
