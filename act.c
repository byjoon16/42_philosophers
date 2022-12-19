/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:13:25 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/14 19:24:54 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	help_eating(t_info *info, int i)
{
	if (print_status(info, info->philo[i].id, EAT) == FALSE)
		return (FALSE);
	info->philo[i].time_to_die = get_time();
	exec_action(info->input.time_to_eat);
	while (1)
	{
		if (get_time() - info->philo[i].time_to_die >= info->input.time_to_eat)
			break ;
	}
	drop_forks(info, i);
	return (TRUE);
}

int	eating(t_info *info, int i)
{
	if (i + 1 == info->input.num_philo)
	{
		if (pthread_mutex_lock(&info->forks[info->philo[i].fork.right]) != 0)
			return (FALSE);
		if (print_status(info, info->philo[i].id, FORK) == FALSE)
			return (FALSE);
		if (pthread_mutex_lock(&info->forks[info->philo[i].fork.left]) != 0)
			return (FALSE);
		if (print_status(info, info->philo[i].id, FORK) == FALSE)
			return (FALSE);
	}
	else
	{
		if (pthread_mutex_lock(&info->forks[info->philo[i].fork.left]) != 0)
			return (FALSE);
		if (print_status(info, info->philo[i].id, FORK) == FALSE)
			return (FALSE);
		if (pthread_mutex_lock(&info->forks[info->philo[i].fork.right]) != 0)
			return (FALSE);
		if (print_status(info, info->philo[i].id, FORK) == FALSE)
			return (FALSE);
	}
	return (help_eating(info, i));
}

int	drop_forks(t_info *info, int i)
{
	if (pthread_mutex_unlock(&info->forks[info->philo[i].fork.left]))
		return (FALSE);
	if (pthread_mutex_unlock(&info->forks[info->philo[i].fork.right]))
		return (FALSE);
	info->philo[i].num_of_times_ate++;
	return (TRUE);
}

int	sleeping(t_info *info, int i)
{
	long long	start;

	if (print_status(info, info->philo[i].id, SLEEP) == FALSE)
		return (FALSE);
	start = get_time();
	exec_action(info->input.time_to_sleep);
	while (1)
	{
		if (get_time() - start >= info->input.time_to_sleep)
			break ;
	}
	return (TRUE);
}

int	philo_dead(t_info *info, int *i)
{
	int	time;

	if (*i == info->input.num_philo)
		*i = 0;
	time = passed_time(info->philo[*i].time_to_die);
	if (time > info->input.time_to_die)
	{
		print_status(info, info->philo[*i].id, DIED);
		info->philo_dead = TRUE;
		return (TRUE);
	}
	*i += 1;
	return (FALSE);
}

