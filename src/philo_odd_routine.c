/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_odd_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:24:09 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 18:51:03 by rkhelif          ###   ########.fr       */
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

void	*routine_odd(void *pa)
{
	t_philo	*p;
	int		tmp;

	p = (t_philo *)pa;
	tmp = p->data->die;
	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
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
	pthread_mutex_lock(&p->data->pr_order);
	if ((p->num_philo % 2) != (p->data->order %2))
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
	while (tmp == 0)
	{
		if (p->nbr_eat > 0)
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
			{
				lock_unlock_mutex_wave_3(p);
			}
		}
		if (((p->data->order % 2) == (p->num_philo % 2))
			&& (p->num_philo != p->data->nbr_philo))
		{
			lock_mutex_wave_1(p);
			take_fork_and_display(p);
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			ft_time(p, p->eating);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
			unlock_mutex_wave_1(p);
		}
		else if (((p->data->order % 2) != (p->num_philo % 2))
			&& (p->num_philo != p->data->nbr_philo))
		{
			find_first_elem(p);
			pthread_mutex_lock(&p->data->pr_temp);
			pthread_mutex_unlock(&p->data->pr_temp);
			lock_mutex_wave_2(p);
			lock_unlock_mutex_wave_1(p);
			pthread_mutex_lock(p->right);
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			ft_time(p, p->eating);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
			unlock_mutex_wave_2(p);
		}
		else
		{
			pthread_mutex_lock(&p->data->wave_3);
			lock_unlock_mutex_wave_2(p);
			lock_unlock_mutex_wave_1(p);
			take_fork_and_display2(p);
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			ft_time(p, p->eating);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(&p->data->wave_3);
		}
		p->nbr_eat++;
		display_sleeping_odd(p);
		ft_time(p, p->sleeping);
		display_thinking_odd(p);
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
	}
	pthread_mutex_lock(&p->data->pr_data_table);
	p->data->table--;
	pthread_mutex_unlock(&p->data->pr_data_table);
	return (NULL);
}

