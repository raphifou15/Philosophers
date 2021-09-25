/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:57:24 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/25 18:43:53 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philosophers(t_data_philo *p)
{
    p->time_begin = time_now();
	if (p->nbr_philo <= 1)
		return (one_philo_or_less_eat(p));
	return (0);
}

/*
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
		p->philo[i].last_meal = time_now();
	i = 0;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_join(p->philo[i].th, NULL) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(7));
	}*/

