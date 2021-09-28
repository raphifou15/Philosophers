/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:07:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/28 20:57:34 by rkhelif          ###   ########.fr       */
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
	int				table;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_philo_must_eat;
	signed long		time_begin;
	char			str[80];
	int				order;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	
	pthread_mutex_t	pr_data_die;
	pthread_mutex_t	pr_data_table;
	pthread_mutex_t	pr_print;
	pthread_mutex_t	wait_all;
	pthread_mutex_t	pr_time;
	pthread_mutex_t	pr_order;

	pthread_mutex_t	wave_1;
	pthread_mutex_t	wave_2;
	pthread_mutex_t	wave_3;
	
}					t_data_philo;

int					main(int argc, char *argv[]);
int					init_philo(t_data_philo *p, char **argv);
int					init_philo_part2(t_data_philo *p);
void				init_philo_part3(t_data_philo *p);

int					ft_philosophers(t_data_philo *p);

int					one_philo_or_less_eat(t_data_philo *p);

void				*routine(void *pa);

int					check_error(int argc, char **argv);
int					check_argv_are_number(int argc, char **argv);
int					err_msg(int err);

int					ft_atoi_m(char *str);
void				ft_putstr_err(char *str);
void				ft_putchar(char c);
unsigned long		time_now(void);
void				ft_putstr(char *str);
void				ft_putnbr_unsigned_long(unsigned long n);
void				str_join(char *str1, char *str2);

int					ft_free(t_data_philo *p);
int					destroy_mutex(t_data_philo *p);

char				*ft_itoa(unsigned long nbr, char *str);
void				ft_bzero(char *str);

int					philo_pair(t_data_philo *p, int i);

void				display_fork_right(t_philo *p);
void				display_fork_left(t_philo *p);
void				display_eating(t_philo *p);
void				display_sleeping(t_philo *p);
void				display_thinking(t_philo *p);

int					philo_odd(t_data_philo *p);

#endif
