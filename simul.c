/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:18:51 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/08 16:29:02 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_info *info, int id, char *status)
{
	long long	now;

	now = 0;
	pthread_mutex_lock(&info->write);
	if (info->philo_dead == TRUE && info->input.num_philo != 1)
	{
		pthread_mutex_unlock(&info->write);
		return (FALSE);
	}
	else
	{
		now = passed_time(info->tt);
		printf("%-10lld %-3d %-30s\n", now, id, status);
	}
	pthread_mutex_unlock(&info->write);
	return (TRUE);
}

int	action_go(t_info *info, int i)
{
	if (eating(info, i) == FALSE)
		return (FALSE);
	if (info->input.num_of_times_eat != info->philo[i].num_of_times_ate)
	{
		if (sleeping(info, i) == FALSE)
			return (FALSE);
		if (print_status(info, info->philo[i].id, THINK) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	*simulation(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	i = info->thread_num;
	if (info->input.num_of_times_eat > 0)
	{
		while (info->input.num_of_times_eat > info->philo[i].num_of_times_ate
			&& info->philo_dead == FALSE)
			action_go(info, i);
	}
	else
	{
		while (info->philo_dead == FALSE)
		{
			if (action_go(info, i) == FALSE)
				break ;
		}
	}
	return (NULL);
}

void	*checker(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	i = 0;
	if (info->input.num_of_times_eat > 0)
	{
		while (info->input.num_of_times_eat > info->philo[i].num_of_times_ate
			&& info->philo_dead == FALSE)
		{
			if (philo_dead(info, &i) == TRUE)
				break ;
		}
	}
	else
	{
		while (info->philo_dead == FALSE)
		{
			if (philo_dead(info, &i) == TRUE)
				break ;
		}
	}
	return (NULL);
}
