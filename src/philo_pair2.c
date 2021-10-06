/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pair2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 04:21:41 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 05:56:34 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die_philo_pair2_next(t_data_philo *p, int eat)
{
	if (eat == p->nbr_philo)
	{
		pthread_mutex_lock(&p->pr_data_die);
		p->die = 1;
		pthread_mutex_unlock(&p->pr_data_die);
		return (1);
	}
	return (0);
}

int	die_philo_pair2(t_data_philo *p, int stop_check)
{
	int				i;
	unsigned long	time;
	int				eat;

	eat = 0;
	i = -1;
	if (stop_check > 0)
		return (1);
	while (++i < p->nbr_philo)
	{
		time = time_now();
		pthread_mutex_lock(&p->pr_time);
		if (time - p->time_begin >= (unsigned long)p->t_die
			&& time - p->philo[i].last_meal >= (unsigned long)p->t_die)
		{
			pthread_mutex_unlock(&p->pr_time);
			display_die_odd(p, time, i);
			return (1);
		}
		if (p->philo[i].have_eating_max == 1)
			eat++;
		pthread_mutex_unlock(&p->pr_time);
	}
	return (die_philo_pair2_next(p, eat));
}

void	philo_pair2_2(t_data_philo *p, int tmp, int tmp2)
{
	int	i;

	i = -1;
	while (tmp > 0)
	{
		pthread_mutex_lock(&p->pr_data_table);
		tmp = p->table;
		pthread_mutex_unlock(&p->pr_data_table);
		if (die_philo_pair2(p, tmp2) == 1)
			tmp2 = 2;
		usleep(1);
	}
	while (++i < p->nbr_philo)
		pthread_join(p->philo[i].th, NULL);
}

int	philo_pair2(t_data_philo *p)
{
	int	i;
	int	tmp;
	int	tmp2;

	tmp2 = 0;
	p->table = p->nbr_philo;
	tmp = p->table;
	i = -1;
	if (p->t_philo_must_eat == 0)
		return (0);
	pthread_mutex_lock(&p->wait_all);
	while (++i < p->nbr_philo)
	{
		pthread_create(&p->philo[i].th, NULL, routine_pair2,
			(void *)&p->philo[i]);
	}
	p->time_begin = time_now();
	pthread_mutex_unlock(&p->wait_all);
	philo_pair2_2(p, tmp, tmp2);
	return (0);
}
