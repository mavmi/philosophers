/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:26:43 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/08/31 15:19:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_UTILS_H
# define DATA_UTILS_H

# define GOT_FORK "has taken a fork"
# define IS_EATING "is eating"
# define IS_SLEEPING "is sleeping"
# define IS_THINKING "is thinking"
# define DIED "died"

# include "utils.h"
# include "philo_thread_funcs.h"
# include "handler_thread_funcs.h"

void	release_data(t_data *data, int forks, int philos, int print_mutex);
int		start_threads(t_data *data);
int		init_philo(t_data *data, int num);
int		init_threads(t_data *data);
int		init_mutex(t_data *data);

#endif
