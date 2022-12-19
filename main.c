/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:57:07 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/08 16:29:40 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long long	passed_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	exec_action(long long time)
{
	usleep(time * 500);
}

int	alone(t_info *info)
{
	long long	start;

	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (FALSE);
	info->tt = get_time();
	print_status(info, 1, FORK);
	start = get_time();
	usleep(info->input.time_to_die * 500);
	while (1)
	{
		if (get_time() - start >= info->input.time_to_die)
			break ;
	}
	print_status(info, 1, DIED);
	ft_free(info);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ft_error(ac, av, &info) == FALSE)
		return (1);
	if (init_philos(&info) == FALSE)
		return (1);
	if (init_forks(&info) == FALSE)
		return (1);
	if (info.input.num_philo == 1)
	{
		if (alone(&info) == FALSE)
			return (1);
		return (0);
	}
	if (create_threads(&info) == FALSE)
		return (1);
	if (destroy_mutex(&info) == FALSE)
		return (1);
	ft_free(&info);
	return (0);
}
