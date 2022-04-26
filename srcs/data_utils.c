/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:27:50 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/31 15:21:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data_utils.h"

// Destroy data array
void	release_data(t_data *data, int forks, int philos, int print_mutex)
{
	int	iter;

	if (data->forks)
	{
		iter = 0;
		while (iter < forks)
		{
			pthread_mutex_destroy(data->forks + iter);
			iter++;
		}
		free(data->forks);
	}
	if (print_mutex)
		pthread_mutex_destroy(&data->print_mutex);
	if (philos)
	{
		iter = 0;
		while (iter < philos)
		{
			pthread_mutex_destroy(&data->philos[iter].eating_mutex);
			iter++;
		}
	}
	free(data->philos);
	free(data);
}

// Start threads in stuct data
// Return 0 if everything is ok
int	start_threads(t_data *data)
{
	int	iter;

	iter = 0;
	gettimeofday(&data->start_time, 0);
	while (iter < data->philo_count)
	{
		if (pthread_create(&data->philos[iter].thread,
				0, philo_func, &data->philos[iter]))
		{
			release_data(data, data->philo_count, data->philo_count, 1);
			return (1);
		}
		pthread_detach(data->philos[iter++].thread);
	}
	if (pthread_create(&data->handler_thread, 0, handler_func, data))
	{
		release_data(data, data->philo_count, data->philo_count, 1);
		return (1);
	}
	pthread_join(data->handler_thread, NULL);
	return (0);
}

int	init_philo(t_data *data, int num)
{
	t_philo	*philo;

	philo = &data->philos[num];
	philo->meal_count = 0;
	philo->number = num + 1;
	philo->is_ready_to_quit = 0;
	philo->data = data;
	philo->first_fork = &data->forks[num];
	if (num == 0)
		philo->second_fork = &data->forks[data->philo_count - 1];
	else
		philo->second_fork = &data->forks[num - 1];
	if (pthread_mutex_init(&philo->eating_mutex, NULL))
	{
		release_data(data, data->philo_count, num, 1);
		return (1);
	}
	return (0);
}

// Init threads in struct data
// Return 0 if everything is fine
int	init_threads(t_data *data)
{
	int		iter;

	data->philos = (t_philo *)malloc(data->philo_count
			* sizeof(t_philo));
	if (!data->philos)
	{
		release_data(data, data->philo_count, 0, 1);
		return (1);
	}	
	iter = 0;
	while (iter < data->philo_count)
	{
		if (init_philo(data, iter))
			return (1);
		iter++;
	}
	return (0);
}

// Init mutex in struct data
// Return 0 if everything is fine
int	init_mutex(t_data *data)
{
	int	iter;

	data->forks = (pthread_mutex_t *)malloc(data->philo_count
			* sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		release_data(data, 0, 0, 0);
		return (1);
	}
	iter = 0;
	while (iter < data->philo_count)
	{
		if (pthread_mutex_init(data->forks + iter++, NULL))
		{
			release_data(data, iter, 0, 0);
			return (1);
		}
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		release_data(data, iter, 0, 1);
		return (1);
	}
	return (0);
}
