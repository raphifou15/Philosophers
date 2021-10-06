/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pair2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 04:33:17 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 17:36:39 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wave_1(t_philo *p)
{
	lock_mutex_wave_1_pair2(p);
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

void	wave_2(t_philo *p)
{
	find_first_elem(p);
	lock_mutex_wave_2(p);
	lock_unlock_mutex_wave_1(p);
	take_fork_and_display2(p);
	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
	display_eating_odd(p);
	ft_time(p, p->eating);
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
	unlock_mutex_wave_2(p);
}

void	loop_pair2(t_philo *p)
{
	if ((p->data->order % 2) == (p->num_philo % 2))
		wave_1(p);
	else
		wave_2(p);
	p->nbr_eat++;
	display_sleeping_odd(p);
	ft_time(p, p->sleeping);
	display_thinking_odd(p);
}

void	*routine_pair2(void *pa)
{
	t_philo	*p;
	int		tmp;

	p = (t_philo *)pa;
	tmp = p->data->die;
	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
	wait_elem_routine_pair2(p);
	while (tmp == 0)
	{
		loop_pair2(p);
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
	}
	pthread_mutex_lock(&p->data->pr_data_table);
	p->data->table--;
	pthread_mutex_unlock(&p->data->pr_data_table);
	return (NULL);
}
