/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:07:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 22:37:22 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data_philo	t_data_philo;

typedef struct s_philo
{
	pthread_t		th;
	int				num_philo;
	unsigned long	eating;
	unsigned long	sleeping;
	int				have_eating_max;
	int				nbr_eat;
	int				die;
	unsigned long	last_meal;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*mutex;
	t_data_philo	*data;
}					t_philo;

typedef struct s_data_philo
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
}					t_data_philo;

int					main(int argc, char *argv[]);
int					init_philo(t_data_philo *p, char **argv);
int					init_philo_part2(t_data_philo *p);
void				init_philo_part3(t_data_philo *p);
int					ft_philosophers(t_data_philo *p);

void				*routine(void *pa);
int					start_take_fork_right(t_philo *p, int i);
int					start_take_fork_left(t_philo *p, int i);
int					start_eating(t_philo *p, int i);
int					start_sleeping_and_thinking(t_philo *p);

void				next_start_eating(t_philo *p);
int					philo_less_than_1_left(t_philo *p);
int					philo_less_than_1_right(t_philo *p);

int					check_if_alive(t_philo *p);
void				ft_check_if_die_during_eating(t_philo *p);
void				ft_check_if_die_during_sleeping(t_philo *p);

int					check_error(int argc, char **argv);
int					check_argv_are_number(int argc, char **argv);
int					err_msg(int err);

int					ft_atoi_m(char *str);
void				ft_putstr_err(char *str);
unsigned long		time_now(void);

int					ft_free(t_data_philo *p);
void				destroy_mutex(t_data_philo *p);

#endif
