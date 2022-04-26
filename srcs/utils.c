/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 18:36:58 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/30 15:17:43 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	is_minus;
	int	result;

	i = 0;
	is_minus = 0;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_minus = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (is_minus)
		result *= -1;
	return (result);
}

// Determines how mush time has passed since beginnig to end.
// If end is NULL, current time will be used.
// Rerurn timestamp in microseconds
long int	get_timestamp(struct timeval *end, struct timeval *beginnig)
{
	struct timeval	current_time;

	if (!end)
	{
		gettimeofday(&current_time, 0);
		return ((current_time.tv_sec - beginnig->tv_sec) * 1e+6
			+ (current_time.tv_usec - beginnig->tv_usec));
	}
	return ((end->tv_sec - beginnig->tv_sec) * 1e+6
		+ (end->tv_usec - beginnig->tv_usec));
}

void	my_sleep(long int milliseconds)
{
	long int		microseconds;
	struct timeval	begin;
	struct timeval	current;

	microseconds = milliseconds * 1e+3;
	gettimeofday(&begin, 0);
	while (1)
	{
		gettimeofday(&current, 0);
		if (get_timestamp(&current, &begin) >= microseconds)
		{
			break ;
		}
		usleep(USLEEP_DELAY);
	}
}

void	print_msg(int time, int philo, char *message)
{
	printf("%dms %d %s\n", time, philo, message);
}
