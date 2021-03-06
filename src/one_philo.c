/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:47:42 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 06:12:54 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_1philo_2(t_philo *p, int tmp)
{
	tmp = 0;
	while (!tmp)
	{	
		pthread_mutex_lock(&p->data->mutex);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->mutex);
	}
	pthread_mutex_unlock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	p->data->table--;
	pthread_mutex_unlock(&p->data->mutex);
}

void	*routine_1philo(void *pa)
{
	t_philo			*p;
	unsigned long	time;

	p = (t_philo *)pa;
	pthread_mutex_lock(p->right);
	pthread_mutex_lock(&p->data->mutex);
	time = time_now();
	str_join(p->data->str, "\e[11;32mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " has taken a fork right\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
	pthread_mutex_unlock(&p->data->mutex);
	routine_1philo_2(p, 0);
	return (NULL);
}

int	die_1philo(t_data_philo *p, int stop_check)
{
	unsigned long	time;

	if (stop_check)
		return (1);
	time = time_now();
	if (time - p->time_begin >= (unsigned long)p->t_die)
	{
		p->die = 1;
		str_join(p->str, "\e[15;31mtimestamp: ");
		ft_itoa(time - p->time_begin, p->str);
		str_join(p->str, "  ");
		ft_itoa(p->philo[0].num_philo, p->str);
		str_join(p->str, " died\e[0m\n");
		ft_putstr(p->str);
		ft_bzero(p->str);
		return (1);
	}
	return (0);
}

int	one_philo_or_less_eat(t_data_philo *p)
{
	int	tmp;
	int	tmp2;

	tmp2 = 0;
	p->table = 1;
	if (p->nbr_philo == 0)
		return (0);
	if (p->t_philo_must_eat == 0)
		return (0);
	p->time_begin = time_now();
	pthread_create(&p->philo[0].th, NULL, routine_1philo, (void *)&p->philo[0]);
	pthread_detach(p->philo[0].th);
	tmp = 1;
	pthread_mutex_lock(&p->mutex);
	p->time_begin = time_now();
	pthread_mutex_unlock(&p->mutex);
	while (tmp)
	{
		pthread_mutex_lock(&p->mutex);
		tmp = p->table;
		if (die_1philo(p, tmp2))
			tmp2 = 2;
		pthread_mutex_unlock(&p->mutex);
	}
	return (0);
}
