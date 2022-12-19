/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:57:28 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/14 19:28:14 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

typedef struct s_input
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_eat;
}					t_input;

typedef struct s_fork
{
	int				left;
	int				right;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				num_of_times_ate;
	long long		time_to_die;
	t_fork			fork;
	pthread_t		thread;
}					t_philo;

typedef struct s_info
{
	int				thread_num;
	int				philo_dead;
	long long		tt;
	t_input			input;
	t_philo			*philo;
	pthread_t		to_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}					t_info;

// act.c
int			help_eating(t_info *info, int i);
int			eating(t_info *info, int i);
int			drop_forks(t_info *info, int i);
int			sleeping(t_info *info, int i);
int			philo_dead(t_info *info, int *i);

// error.c
int			ft_error(int ac, char **av, t_info *info);
void		print_error(t_info *info, int ac);
int			init_input(int ac, char **av, t_info *info);

// init.c
int			init_forks(t_info *info);
int			init_philos(t_info *info);
void		fill_philo(t_info *info, int i, int j);
void		unlock_forks(t_info *info);

// thread.c
int			create_threads(t_info *info);
int			join_threads(t_info *info);
int			destroy_mutex(t_info *info);

// simul.c
int			action_go(t_info *info, int i);
void		*simulation(void *args);
int			print_status(t_info *info, int id, char *status);
void		*checker(void *args);

// main.c
long long	get_time(void);
long long	passed_time(long long time2);
void		exec_action(long long time);
int			alone(t_info *info);

// help.c
void		ft_free(t_info *info);
int			philo_atoi(char *str);

#endif
