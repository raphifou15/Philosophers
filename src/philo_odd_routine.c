/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_odd_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:24:09 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 20:00:53 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_and_display(t_philo *p)
{
	pthread_mutex_lock(p->left);
	display_fork_left_odd(p);
	pthread_mutex_lock(p->right);
	display_fork_right_odd(p);
}

void	take_fork_and_display2(t_philo *p)
{
	pthread_mutex_lock(p->right);
	display_fork_right_odd(p);
	pthread_mutex_lock(p->left);
	display_fork_left_odd(p);
}

void	eat_more_than_one(t_philo *p)
{
	if (((p->data->order % 2) == (p->num_philo % 2))
		&& (p->num_philo != p->data->nbr_philo))
	{
		pthread_mutex_lock(&p->data->pr_order);
		if (p->data->order == p->num_philo)
		{
			pthread_mutex_unlock(&p->data->pr_order);
			pthread_mutex_lock(&p->data->pr_temp);
		}
		else
			pthread_mutex_unlock(&p->data->pr_order);
		lock_unlock_mutex_wave_3(p);
	}
	if (((p->data->order % 2) != (p->num_philo % 2))
		&& (p->num_philo != p->data->nbr_philo))
		lock_unlock_mutex_wave_3(p);
}

void	*routine_odd(void *pa)
{
	t_philo	*p;
	int		tmp;

	p = (t_philo *)pa;
	tmp = p->data->die;
	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
	wait_elem_routine(p);
	while (tmp == 0)
	{
		if (p->nbr_eat > 0)
			eat_more_than_one(p);
		loop_odd(p);
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
	}
	pthread_mutex_lock(&p->data->pr_data_table);
	p->data->table--;
	pthread_mutex_unlock(&p->data->pr_data_table);
	return (NULL);
}
