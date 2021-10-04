/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:24:18 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 01:36:22 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_thinking_odd(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	pthread_mutex_lock(&p->data->pr_data_die);
	if (p->data->die != 0)
	{
		pthread_mutex_unlock(&p->data->pr_data_die);
		return ;
	}
	pthread_mutex_unlock(&p->data->pr_data_die);
    pthread_mutex_lock(&p->data->pr_print);
	str_join(p->data->str, "\e[1;37mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " is thinking \e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}


void	display_sleeping_odd(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	pthread_mutex_lock(&p->data->pr_data_die);
	if (p->data->die != 0)
	{
		pthread_mutex_unlock(&p->data->pr_data_die);
		return ;
	}
	pthread_mutex_unlock(&p->data->pr_data_die);
    pthread_mutex_lock(&p->data->pr_print);
	str_join(p->data->str, "\e[1;36mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " is sleeping \e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_eating_odd(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	pthread_mutex_lock(&p->data->pr_data_die);
	if (p->data->die != 0)
	{
		pthread_mutex_unlock(&p->data->pr_data_die);
		return ;
	}
	pthread_mutex_unlock(&p->data->pr_data_die);
	pthread_mutex_lock(&p->data->mutex);
	if (p->nbr_eat + 1 == p->data->t_philo_must_eat)
		p->have_eating_max = 1;
	pthread_mutex_unlock(&p->data->mutex);
    pthread_mutex_lock(&p->data->pr_print);
	str_join(p->data->str, "\e[15;33mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " is eating  nbr_eating: ");
	ft_itoa((p->nbr_eat + 1), p->data->str);
	str_join(p->data->str, "\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}


void	display_fork_right_odd(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	pthread_mutex_lock(&p->data->pr_data_die);
	if (p->data->die != 0)
	{
		pthread_mutex_unlock(&p->data->pr_data_die);
		return ;
	}
	pthread_mutex_unlock(&p->data->pr_data_die);
    pthread_mutex_lock(&p->data->pr_print);
	str_join(p->data->str, "\e[11;32mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " has taken a fork right\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_fork_left_odd(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	pthread_mutex_lock(&p->data->pr_data_die);
	if (p->data->die != 0)
	{
		pthread_mutex_unlock(&p->data->pr_data_die);
		return ;
	}
	pthread_mutex_unlock(&p->data->pr_data_die);
    pthread_mutex_lock(&p->data->pr_print);
	str_join(p->data->str, "\e[1;32mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " has taken a fork left\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}


void	display_wave_1(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;35m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_wave_2(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;36m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_wave_3(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;33m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\n\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}
