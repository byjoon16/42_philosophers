/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:50:34 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/07 19:10:01 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->input.num_philo);
	if (info->forks == NULL)
		return (FALSE);
	i = 0;
	while (i < info->input.num_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	init_philos(t_info *info)
{
	int	i;
	int	j;

	info->philo = malloc(sizeof(t_philo) * info->input.num_philo);
	if (info->philo == NULL)
		return (FALSE);
	i = 0;
	j = 1;
	while (j < info->input.num_philo)
	{
		fill_philo(info, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo(info, i, j);
	return (TRUE);
}

void	fill_philo(t_info *info, int i, int j)
{
	info->philo[i].id = i + 1;
	info->philo[i].num_of_times_ate = 0;
	info->philo[i].time_to_die = 0;
	info->philo[i].fork.left = i;
	info->philo[i].fork.right = j;
}

void	unlock_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philo)
	{
		pthread_mutex_unlock(&info->forks[i]);
		i++;
	}
}
