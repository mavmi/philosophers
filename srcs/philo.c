/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 18:36:14 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/30 17:43:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data_utils.h"
#include "../include/input_parser.h"

// Init data struct and start threads
// May return NULL
static t_data	*init_data_struct(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->finish = 0;
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->each_must_eat = -1;
	else
		data->each_must_eat = ft_atoi(argv[5]);
	data->philos = NULL;
	data->forks = NULL;
	if (init_mutex(data) || init_threads(data) || start_threads(data))
		return (NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parse_input(argc, argv))
	{
		return (1);
	}
	data = init_data_struct(argc, argv);
	if (!data)
	{
		return (1);
	}
	return (0);
}
