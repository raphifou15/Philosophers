/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:28:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/26 16:59:21 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo_pair(void *pa)
{
	int				tmp;
	t_philo			*p;
	unsigned long	time;

	p = (t_philo *)pa;
	pthread_mutex_lock(&p->data->mutex);
	tmp =  p->data->die;
	pthread_mutex_unlock(&p->data->mutex);
	while (tmp == 0)
	{
		if (p->num_philo % 2 != 0)
		{
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(p->right);
			time = time_now();
			pthread_mutex_lock(&p->data->mutex);
		
			str_join(p->data->str, "\e[1;32mtimestamp: ");
			ft_itoa(time - p->data->time_begin, p->data->str);
			str_join(p->data->str, "  ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, " has taken a fork left\e[0m\n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);

			str_join(p->data->str, "\e[11;32mtimestamp: ");
			ft_itoa(time - p->data->time_begin, p->data->str);
			str_join(p->data->str, "  ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, " has taken a fork right\e[0m\n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
		
			tmp = p->data->die;
			ft_putstr("finnish and die\n");
			
			tmp = p->data->die;
			pthread_mutex_unlock(&p->data->mutex);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
		}
		else
		{
			pthread_mutex_lock(p->right);
			pthread_mutex_lock(p->left);
			time = time_now();
			pthread_mutex_lock(&p->data->mutex);
			
			str_join(p->data->str, "\e[11;32mtimestamp: ");
			ft_itoa(time - p->data->time_begin, p->data->str);
			str_join(p->data->str, "  ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, " has taken a fork right\e[0m\n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);

			str_join(p->data->str, "\e[1;32mtimestamp: ");
			ft_itoa(time - p->data->time_begin, p->data->str);
			str_join(p->data->str, "  ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, " has taken a fork left\e[0m\n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			tmp = p->data->die;
			ft_putstr("finnish and die\n");
			pthread_mutex_unlock(&p->data->mutex);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
		}
	}
	pthread_mutex_lock(&p->data->mutex);
	p->data->table--;
	pthread_mutex_unlock(&p->data->mutex);
	return (NULL);
}

int	die_philo_pair(t_data_philo *p, int stop_check)
{
	if (stop_check > 0)
		return (1);
	p->die = 1;
	ft_putstr("il y a eu un mort\n");
	return (1);
	//return (0);
}

int	philo_pair(t_data_philo *p, int i)
{
	int	tmp;
	int	tmp2;

	tmp2 = 0;
	p->table = p->nbr_philo;
	tmp = p->table;
	if (p->t_philo_must_eat == 0)
		return (0);
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
	{
		pthread_create(&p->philo[i].th, NULL, routine_philo_pair,
		(void *)&p->philo[i]);
		pthread_detach(p->philo[i].th);
	}
	pthread_mutex_lock(&p->mutex);
	p->time_begin = time_now();
	pthread_mutex_unlock(&p->mutex);
	while (tmp > 0)
	{
		pthread_mutex_lock(&p->mutex);
		tmp = p->table;
		if (die_philo_pair(p, tmp2) == 1)
			tmp2 = 2;
		pthread_mutex_unlock(&p->mutex);
	}
	return (0);
}
