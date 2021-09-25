/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:47:42 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/25 23:09:06 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_1philo(void *pa)
{
    t_philo			*p;
    int 			tmp;
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
    return (NULL);
}

int		die_1philo(t_data_philo *p, int stop_check, char *str)
{
	unsigned long	time;
	
	str[0] = '\0';
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

int one_philo_or_less_eat(t_data_philo *p)
{
	int	tmp;
	int	tmp2;
	char	*str;

	str = malloc(sizeof(char) * 500);
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
		if (die_1philo(p, tmp2, str))
			tmp2 = 2;	
		pthread_mutex_unlock(&p->mutex);
	}
	free(str);
    return (0);
}
    /*while (1)
    {
        pthread_mutex_lock(&p->mutex);
		if (p->philo[0].die == 1)
			p->die = 1;
		if (p->die == 1)
		{
    		pthread_mutex_unlock(&p->mutex);
			break ;
		}
        pthread_mutex_unlock(&p->mutex);
		usleep(100);
    }*/
	//usleep(1000);
	//pthread_join(p->philo[0].th, NULL);
	//pthread_detach(p->philo[0].th);

/*
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
		p->philo[i].last_meal = time_now();
	i = 0;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_join(p->philo[i].th, NULL) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(7));
	}*/
