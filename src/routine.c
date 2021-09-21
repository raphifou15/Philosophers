/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:13:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 22:21:26 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_take_fork_right(t_philo *p, int i)
{
	t_data_philo	*pr;

	pr = p->data;
	pthread_mutex_lock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	while (++i < p->data->nbr_philo && p->data->philo[i].have_eating_max == 1)
		;
	if (i == p->data->nbr_philo)
		p->data->die = 1;
	if (check_if_alive(p) == 1)
		return (1);
	printf("\e[11;32mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d has taken a fork right\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	if (p->data->nbr_philo <= 1)
		return (philo_less_than_1_right(p));
	pthread_mutex_lock(p->left);
	pthread_mutex_lock(&p->data->mutex);
	if (check_if_alive(p) == 1)
		return (1);
	printf("\e[1;32mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d has taken a fork left\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}

int	start_take_fork_left(t_philo *p, int i)
{
	t_data_philo	*pr;

	pr = p->data;
	pthread_mutex_lock(p->left);
	pthread_mutex_lock(&p->data->mutex);
	while (++i < p->data->nbr_philo && p->data->philo[i].have_eating_max == 1)
		;
	if (i == p->data->nbr_philo)
		p->data->die = 1;
	if (check_if_alive(p) == 1)
		return (1);
	printf("\e[1;32mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d has taken a fork left\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	if (p->data->nbr_philo <= 1)
		return (philo_less_than_1_left(p));
	pthread_mutex_lock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	if (check_if_alive(p) == 1)
		return (1);
	printf("\e[11;32mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d has taken a fork right\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}

int	start_eating(t_philo *p, int i)
{
	t_data_philo	*pr;

	pr = p->data;
	pthread_mutex_lock(&p->data->mutex);
	if (check_if_alive(p) == 1)
		return (1);
	ft_check_if_die_during_eating(p);
	p->last_meal = time_now();
	p->nbr_eat++;
	printf("\e[15;33mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d is eating  nbr_eating: %d\e[0m\n", p->num_philo, p->nbr_eat);
	pthread_mutex_unlock(&p->data->mutex);
	if (p->data->t_philo_must_eat != -2
		&& p->data->t_philo_must_eat == p->nbr_eat)
		p->have_eating_max = 1;
	while (++i < p->data->nbr_philo && p->data->philo[i].have_eating_max == 1)
		;
	if (i == p->data->nbr_philo)
		p->data->die = 1;
	usleep(p->eating * 1000);
	next_start_eating(p);
	return (0);
}

int	start_sleeping_and_thinking(t_philo *p)
{
	t_data_philo	*pr;

	pr = p->data;
	pthread_mutex_lock(&p->data->mutex);
	if (check_if_alive(p) == 1)
		return (1);
	ft_check_if_die_during_sleeping(p);
	printf("\e[1;36mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d is sleeping\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	usleep(p->sleeping * 1000);
	pthread_mutex_lock(&p->data->mutex);
	if (check_if_alive(p) == 1)
		return (1);
	printf("\e[1;37mtimestamp: %ld   ", time_now() - pr->time_begin);
	printf("%d is thinking\e[0m\n", p->num_philo);
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}

void	*routine(void *pa)
{
	t_philo		*p;

	p = (t_philo *)pa;
	while (p->die >= 0)
	{
		if (p->num_philo % 2 == 0)
		{
			if (start_take_fork_right(p, -1) == 1)
				return (NULL);
		}
		else
		{
			if (start_take_fork_left(p, -1) == 1)
				return (NULL);
		}
		if (start_eating(p, -1) == 1)
			return (NULL);
		if (start_sleeping_and_thinking(p) == 1)
			return (NULL);
	}
	return (NULL);
}
