/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:37:57 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/08 16:51:17 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	info->philo_dead = FALSE;
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (FALSE);
	info->tt = get_time();
	while (i < info->input.num_philo)
	{
		info->philo[i].time_to_die = info->tt;
		info->thread_num = i;
		if (pthread_create(&info->philo[i].thread,
				NULL, &simulation, (void *)info) != 0)
			return (FALSE);
		i++;
		usleep(500);
	}
	if (pthread_create(&info->to_check, NULL, &checker, (void *)info) != 0)
		return (FALSE);
	if (join_threads(info) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_join(info->to_check, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

int	destroy_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	return (TRUE);
}
