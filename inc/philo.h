/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:07:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 05:10:05 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_data_philo t_data_philo;

typedef struct	s_philo
{
	pthread_t		th;
	int				num_philo;
	unsigned long	eating;
	unsigned long	sleeping;
	int				nbr_eat;
	int				die;
	unsigned long	last_meal;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*mutex;
	t_data_philo	*data;
}					t_philo;

typedef	struct	s_data_philo
{
	int				nbr_philo;
	int				die;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_philo_must_eat;
	unsigned long	time_begin;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
}				t_data_philo;

int	main(int argc, char *argv[]);
int	init_philo(t_data_philo *p, char **argv);
int	init_philo_part2(t_data_philo *p);
int	ft_philosophers(t_data_philo *p);

int	check_error(int argc, char **argv);
int	check_argv_are_number(int argc, char **argv);
int	err_msg(int err);

int		ft_atoi_m(char *str);
void	ft_putstr_err(char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int nbr);
unsigned long	time_now(void);

int		ft_free(t_data_philo *p);
void	destroy_mutex(t_data_philo *p);

#endif
