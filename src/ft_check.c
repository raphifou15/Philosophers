/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:06:08 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/24 16:38:08 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_alive(t_philo *p)
{
	unsigned long	die;

	die = (unsigned long)p->die;
	if (p->data->die == 1)
	{
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	if ((time_now() - p->last_meal) >= die)
	{
		printf("\e[15;31mtimestamp: %ld   ", time_now() - p->data->time_begin);
		printf("%d died\e[0m\n", p->num_philo);
		p->data->die = 1;
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	return (0);
}

void	ft_check_if_die_during_eating(t_philo *p)
{
	unsigned long	die;

	die = (unsigned long)p->die;
	if (p->eating >= die)
		p->eating = die;
}

void	ft_check_if_die_during_sleeping(t_philo *p)
{
	unsigned long	time;
	unsigned long	die;

	die = (unsigned long)p->die;
	time = (time_now() - p->last_meal);
	if (time + p->sleeping >= die)
		p->sleeping = die - time;
}

int	ft_check_if_someone_died(t_philo *p)
{
	int	i;
	int x;
	
	i = -1;
	x = 0;
	while (++i < p->data->nbr_philo)
	{
		if (check_if_alive(&p->data->philo[i]) == 1)
			x++;
	}
	return (x);
}
