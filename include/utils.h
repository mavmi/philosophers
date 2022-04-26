/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 18:37:06 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/30 15:17:50 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

int			ft_atoi(const char *str);
long int	get_timestamp(struct timeval *end, struct timeval *beginnig);
void		my_sleep(long int milliseconds);
void		print_msg(int time, int philo, char *message);

#endif
