/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:28:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/27 15:10:49 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_time(t_philo *p, unsigned long time_to_do)
{
	unsigned long	time;

	usleep(((time_to_do * 1000) / 5) * 4);
	time = time_now();
	while (time_to_do > time - p->last_meal)
	{
		usleep(100);
		time = time_now();
	}
}

void	*routine_philo_pair(void *pa)
{
	int				tmp;
	t_philo			*p;

	p = (t_philo *)pa;
	
	pthread_mutex_lock(&p->data->mutex);
	p->data->time_begin = time_now();
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->mutex);
	tmp = 0;
	while (tmp == 0)
	{
		if (p->num_philo % 2 == 0)
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
			if (tmp == 1)
				break ;
			ft_time(p, p->sleeping);
		}
		else
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
			if (tmp == 1)
				break ;
			ft_time(p, p->sleeping);
		}
	}
	pthread_mutex_lock(&p->data->mutex);
	p->data->table--;
	pthread_mutex_unlock(&p->data->mutex);
	return (NULL);
}

int	die_philo_pair(t_data_philo *p, int stop_check)
{
	int	i;
	unsigned long time;
	int				eat;

	eat = 0;
	i = -1;
	if (stop_check > 0)
		return (1);
	time = time_now();
	while (++i < p->nbr_philo)
	{
		if (time - p->time_begin >=  (unsigned long)p->t_die
			&& time - p->philo[i].last_meal >= (unsigned long)p->t_die)
		{
			p->die = 1;
			str_join(p->str, "\e[15;31mtimestamp: ");
			ft_itoa(time - p->time_begin, p->str);
			str_join(p->str, "  ");
			ft_itoa(p->philo[i].num_philo, p->str);
			str_join(p->str, " died\e[0m\n");
			ft_putstr(p->str);
			ft_bzero(p->str);
			return (1);
		}
		if (p->philo[i].have_eating_max == 1)
			eat++;
	}
	if (eat == p->nbr_philo)
	{
		p->die = 1;
		return (1);
	}
	return (0);
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
		usleep(10);
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
		usleep(1);
	}
	i = -1;
	while (++i < p->nbr_philo)
		pthread_join(p->philo[i].th, NULL);
	return (0);
}



/*void	*routine_philo_pair(void *pa)
{
	int				tmp;
	t_philo			*p;

	p = (t_philo *)pa;

	pthread_mutex_lock(&p->data->all_thread);
	pthread_mutex_unlock(&p->data->all_thread);
	pthread_mutex_lock(&p->data->mutex);
	p->data->time_begin = time_now();
	pthread_mutex_unlock(&p->data->mutex);
	tmp = 0;
	while (tmp == 0)
	{
		if (p->num_philo % 2 == 0)
		{
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(p->right);
			pthread_mutex_lock(&p->data->mutex);
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "  \n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			tmp = p->data->die;
			pthread_mutex_unlock(&p->data->mutex);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
			pthread_mutex_lock(&p->data->mutex);
			tmp = p->data->die;
			usleep(1000);
			pthread_mutex_unlock(&p->data->mutex);
		}
		else
		{
			pthread_mutex_lock(p->right);
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(&p->data->mutex);
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "  \n");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			tmp = p->data->die;
			pthread_mutex_unlock(&p->data->mutex);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
			pthread_mutex_lock(&p->data->mutex);
			tmp = p->data->die;
			usleep(1000);
			pthread_mutex_unlock(&p->data->mutex);
		}

	}
	pthread_mutex_lock(&p->data->mutex);
	p->data->table--;
	pthread_mutex_unlock(&p->data->mutex);
	return (NULL);
}

int	die_philo_pair(t_data_philo *p, int stop_check)
{
	int	i;
	unsigned long time;

	i = -1;
	if (stop_check > 0)
		return (1);
	time = time_now();
	while (++i < p->nbr_philo)
	{
		if (time - p->time_begin >= (unsigned long)p->t_die)
		{
			p->die = 1;
			str_join(p->str, "\e[15;31mtimestamp: ");
			ft_itoa(time - p->time_begin, p->str);
			str_join(p->str, "  ");
			ft_itoa(p->philo[i].num_philo, p->str);
			str_join(p->str, " died\e[0m\n");
			ft_putstr(p->str);
			ft_bzero(p->str);
			return (1);
		}
	}
	return (0);
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
	i = -1;
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

*/

		/*
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
			usleep(200);
		}*/
