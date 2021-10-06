/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_elem_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:15:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 03:07:01 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_elem_pivot_0(t_philo *p)
{
	if (p->data->order == 0 && p->num_philo == p->data->nbr_philo)
	{
		p->data->pivot = 1;
	}
	if (p->data->order == 0 && p->data->pivot == 0)
		p->data->order = p->num_philo;
	if (p->data->order2 == 0 && p->data->order % 2 != p->num_philo % 2)
		p->data->order2 = p->num_philo;
	pthread_mutex_lock(&p->data->block_last_elem);
	if (p->data->pivot == 1)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_lock(&p->data->block_last_elem);
		pthread_mutex_unlock(&p->data->block_last_elem);
	}
	else
	{
		pthread_mutex_unlock(&p->data->block_last_elem);
		pthread_mutex_unlock(&p->data->pr_order);
	}
}

void	wait_elem_routine_2(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if ((p->num_philo % 2) != (p->data->order % 2))
	{
		pthread_mutex_unlock(&p->data->pr_order);
		usleep(50);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
	pthread_mutex_lock(&p->data->pr_order);
	if (p->num_philo == p->data->nbr_philo)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		usleep(300);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}

void	wait_elem_routine(t_philo *p)
{
	pthread_mutex_lock(&p->data->wait_all);
	pthread_mutex_unlock(&p->data->wait_all);
	pthread_mutex_lock(&p->data->pr_order);
	pthread_mutex_unlock(&p->data->pr_order);
	pthread_mutex_lock(&p->data->pr_order);
	if (p->data->pivot == 1)
	{
		p->data->pivot = 0;
		if (p->data->order == 0 && p->data->pivot == 0)
			p->data->order = p->num_philo;
		if (p->data->order2 == 0 && p->data->order % 2 != p->num_philo % 2)
			p->data->order2 = p->num_philo;
		pthread_mutex_unlock(&p->data->block_last_elem);
		pthread_mutex_unlock(&p->data->pr_order);
	}
	else
		wait_elem_pivot_0(p);
}
