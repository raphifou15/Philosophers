/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:13:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 02:34:20 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_even(t_philo *p, int tmp)
{
	pthread_mutex_lock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	display_fork_right(p);
	tmp = p->data->die;
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_lock(p->left);
	pthread_mutex_lock(&p->data->mutex);
	p->last_meal = time_now();
	display_fork_left(p);
	tmp = p->data->die;
	display_eating(p);
	pthread_mutex_unlock(&p->data->mutex);
	ft_time(p, p->eating);
	pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
	pthread_mutex_lock(&p->data->mutex);
	tmp = p->data->die;
	display_sleeping(p);
	pthread_mutex_unlock(&p->data->mutex);
	ft_time(p, p->sleeping);
	pthread_mutex_lock(&p->data->mutex);
	display_thinking(p);
	pthread_mutex_unlock(&p->data->mutex);
	return (tmp);
}

int	odd_even(t_philo *p, int tmp)
{
	pthread_mutex_lock(p->left);
	pthread_mutex_lock(&p->data->mutex);
	display_fork_left(p);
	tmp = p->data->die;
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_lock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	display_fork_right(p);
	tmp = p->data->die;
	p->last_meal = time_now();
	display_eating(p);
	pthread_mutex_unlock(&p->data->mutex);
	ft_time(p, p->eating);
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	tmp = p->data->die;
	display_sleeping(p);
	pthread_mutex_unlock(&p->data->mutex);
	ft_time(p, p->sleeping);
	pthread_mutex_lock(&p->data->mutex);
	display_thinking(p);
	pthread_mutex_unlock(&p->data->mutex);
	return (tmp);
}

void	*routine_philo_pair(void *pa)
{
	int		tmp;
	t_philo	*p;

	p = (t_philo *)pa;
	pthread_mutex_lock(&p->data->mutex);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->mutex);
	tmp = 0;
	while (tmp == 0)
	{
		if (p->num_philo % 2 == 0)
			tmp = even_even(p, tmp);
		else
			tmp = odd_even(p, tmp);
	}
	pthread_mutex_lock(&p->data->mutex);
	p->data->table--;
	pthread_mutex_unlock(&p->data->mutex);
	return (NULL);
}
