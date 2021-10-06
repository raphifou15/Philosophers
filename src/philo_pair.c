/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:28:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 03:48:03 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_time(t_philo *p, unsigned long time_to_do)
{
	unsigned long	time;
	unsigned long	time2;

	(void)p;
	time2 = time_now();
	usleep(((time_to_do * 1000) / 5) * 4);
	time = time_now();
	while (time_to_do > time - time2)
	{
		usleep(100);
		time = time_now();
	}
}

int	die_philo_pair(t_data_philo *p, int stop_check)
{
	int				i;
	unsigned long	time;
	int				eat;

	eat = 0;
	i = -1;
	if (stop_check > 0)
		return (1);
	time = time_now();
	while (++i < p->nbr_philo)
	{
		if (time - p->time_begin >= (unsigned long)p->t_die
			&& time - p->philo[i].last_meal >= (unsigned long)p->t_die)
			return (display_die_pair(p, i, time));
		if (p->philo[i].have_eating_max == 1)
			eat++;
	}
	if (eat == p->nbr_philo)
	{
		p->die = 1;
		return (1);
	}
	return (0);
}

void	philo_pair_2(t_data_philo *p, int tmp, int tmp2)
{
	int	i;

	while (tmp > 0)
	{
		pthread_mutex_lock(&p->mutex);
		tmp = p->table;
		if (die_philo_pair(p, tmp2) == 1)
			tmp2 = 2;
		pthread_mutex_unlock(&p->mutex);
	}
	i = -1;
	while (++i < p->nbr_philo)
		pthread_join(p->philo[i].th, NULL);
}

int	philo_pair(t_data_philo *p, int i)
{
	int	tmp;
	int	tmp2;

	tmp2 = 0;
	p->table = p->nbr_philo;
	tmp = p->table;
	if (p->t_philo_must_eat == 0)
		return (0);
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
	{
		pthread_create(&p->philo[i].th, NULL, routine_philo_pair,
			(void *)&p->philo[i]);
		usleep(1);
	}
	philo_pair_2(p, tmp, tmp2);
	return (0);
}
