/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:45:07 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/06 22:02:23 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int ac, char **av, t_info *info)
{
	if (init_input(ac, av, info) == FALSE)
	{
		printf("ERROR: ac must be 5 or 6\n");
		return (FALSE);
	}
	else
	{
		print_error(info, ac);
		if (!info->input.num_philo || !info->input.time_to_die
			|| !info->input.time_to_eat || !info->input.time_to_sleep
			|| (ac == 6 && !info->input.num_of_times_eat))
			return (FALSE);
	}
	return (TRUE);
}

int	init_input(int ac, char **av, t_info *info)
{
	if (ac == 5 || ac == 6)
	{
		info->input.num_philo = philo_atoi(av[1]);
		info->input.time_to_die = philo_atoi(av[2]);
		info->input.time_to_eat = philo_atoi(av[3]);
		info->input.time_to_sleep = philo_atoi(av[4]);
		if (ac == 6)
			info->input.num_of_times_eat = philo_atoi(av[5]);
		else
			info->input.num_of_times_eat = -1;
		return (TRUE);
	}
	return (FALSE);
}

void	print_error(t_info *info, int ac)
{
	if (!info->input.num_philo)
		printf("ERROR: mistake in number of philosophers\n");
	if (!info->input.time_to_die)
		printf("ERROR: mistake in time to die\n");
	if (!info->input.time_to_eat)
		printf("ERROR: mistake in time to eat\n");
	if (!info->input.time_to_sleep)
		printf("ERROR: mistake in time to sleep\n");
	if (ac == 6 && !info->input.num_of_times_eat)
		printf("ERROR: mistake in num of times each philo must eat\n");
}
