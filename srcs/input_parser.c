/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:23:28 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/30 21:13:35 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input_parser.h"

static void	print_error(void)
{
	printf("Wrong input!\n");
	printf("usage: philo [number_of_philosophers] [time_to_die]\n \
[time_to_eat] [time_to_sleep]\n \
[number_of_times_each_philosopher_must_eat]\n");
}

static int	strlen(char *str)
{
	int	counter;

	if (!str)
		return (0);
	counter = 0;
	while (*str)
	{
		counter++;
		str++;
	}
	return (counter);
}

static int	cmp_strings(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			free(s1);
			return (1);
		}
		i++;
	}
	free(s1);
	return (0);
}

// Check if num_str is positive integer
static int	is_valid_number(char *num_str)
{
	int		num;
	char	*checker_str;

	if (!num_str)
		return (1);
	num = ft_atoi(num_str);
	if (num < 0)
		return (1);
	checker_str = ft_itoa(num);
	if (!checker_str)
		return (1);
	if (strlen(checker_str) != strlen(num_str))
	{
		free(checker_str);
		return (1);
	}
	cmp_strings(checker_str, num_str);
	return (0);
}

int	parse_input(int argc, char **argv)
{
	int	iter;

	if (argc != 5 && argc != 6)
	{
		print_error();
		return (1);
	}
	iter = 1;
	while (iter < argc)
	{
		if (is_valid_number(*(argv + iter++)))
		{
			print_error();
			return (1);
		}
	}
	return (0);
}
