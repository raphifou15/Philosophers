/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:23:13 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/04 01:10:53 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

void	lock_mutex_wave_1(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if (p->num_philo == p->data->order)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_lock(&p->data->wave_1);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}


void	unlock_mutex_wave_1(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if (p->num_philo == p->data->order)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_unlock(&p->data->wave_1);
		if (p->nbr_eat > 0)
			pthread_mutex_unlock(&p->data->pr_temp);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}

void	find_first_elem(t_philo *p)
{
	int	tmp;

	pthread_mutex_lock(&p->data->pr_tour);
	tmp = p->data->tour;
	if (tmp == 0)
	{
		pthread_mutex_lock(&p->data->pr_order);
		p->data->order2 = p->num_philo;
		pthread_mutex_unlock(&p->data->pr_order);
	}
	p->data->tour = 1;
	pthread_mutex_unlock(&p->data->pr_tour);
}

void	find_first_elem2(t_philo *p)
{
	int	tmp;

	pthread_mutex_lock(&p->data->pr_tour);
	tmp = p->data->tour;
	pthread_mutex_unlock(&p->data->pr_tour);
	if (tmp == 0)
	{
		pthread_mutex_lock(&p->data->pr_order);
		p->data->order = p->num_philo;
		pthread_mutex_unlock(&p->data->pr_order);
	}
	pthread_mutex_lock(&p->data->pr_tour);
	p->data->tour = 1;
	pthread_mutex_unlock(&p->data->pr_tour);
}


void    lock_mutex_wave_2(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if (p->data->order2 == p->num_philo)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_lock(&p->data->wave_2);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}

void    unlock_mutex_wave_2(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if (p->data->order2 == p->num_philo)
	{	
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_lock(&p->data->pr_tour);
		p->data->tour = 0;
		pthread_mutex_unlock(&p->data->pr_tour);
		pthread_mutex_unlock(&p->data->wave_2);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}

void	lock_unlock_mutex_wave_1(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_1);
	 pthread_mutex_unlock(&p->data->wave_1);
}

void	lock_unlock_mutex_wave_2(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_2);
	 pthread_mutex_unlock(&p->data->wave_2);
}

void	lock_unlock_mutex_wave_3(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_3);
	 pthread_mutex_unlock(&p->data->wave_3);
}

