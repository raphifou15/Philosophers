/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:25:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/24 15:02:42 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	next_start_eating(t_philo *p)
{
	if (p->num_philo % 2 == 0)
	{
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
	}
	else
	{
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
	}
}

int	philo_less_than_1_left(t_philo *p)
{
	usleep((p->data->t_die - (time_now() - p->last_meal)) * 1000);
	printf("\e[15;31mtimestamp: %ld   ", time_now() - p->data->time_begin);
	printf("%d died\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_unlock(p->left);
	return (1);
}

int	philo_less_than_1_right(t_philo *p)
{
	usleep((p->data->t_die - (time_now() - p->last_meal)) * 1000);
	printf("\e[15;31mtimestamp: %ld   ", time_now() - p->data->time_begin);
	printf("%d died\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_unlock(p->right);
	return (1);
}
