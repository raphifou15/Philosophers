/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:06:08 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/22 15:43:57 by rkhelif          ###   ########.fr       */
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

int	ft_check_if_die_during_eating(t_philo *p)
{
	unsigned long	time;
	unsigned long	die;

	die = (unsigned long)p->die;
	time = (time_now() - p->last_meal);
	if (time + p->eating > die + 4)
	{
		//printf("lala %d\n", p->num_philo);
		p->eating = (die + 4) - time;
			p->nbr_eat++;
		printf("\e[15;33mtimestamp: %ld   ", time_now() - p->data->time_begin);
		printf("%d is eating  nbr_eating: %d\e[0m\n", p->num_philo, p->nbr_eat);
		usleep(p->eating * 1000);
		check_if_alive(p);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	return (0);
}

void	ft_check_if_die_during_sleeping(t_philo *p)
{
	unsigned long	time;
	unsigned long	die;

	die = (unsigned long)p->die;
	time = (time_now() - p->last_meal);
	if (time + p->sleeping > die + 4) 
	{
		//printf("lolo\n");
		p->sleeping = (die + 4) - time;
	}
}
