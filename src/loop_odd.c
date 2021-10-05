/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_odd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:49:49 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 20:56:32 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_odd(t_philo *p)
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

void	odd_odd(t_philo *p)
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

void	other_odd(t_philo *p)
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

void	loop_odd(t_philo *p)
{
	if (((p->data->order % 2) == (p->num_philo % 2))
		&& (p->num_philo != p->data->nbr_philo))
		even_odd(p);
	else if (((p->data->order % 2) != (p->num_philo % 2))
		&& (p->num_philo != p->data->nbr_philo))
		odd_odd(p);
	else
		other_odd(p);
	p->nbr_eat++;
	display_sleeping_odd(p);
	ft_time(p, p->sleeping);
	display_thinking_odd(p);
}
