/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_odd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 22:35:53 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/28 20:30:35 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_odd(void *pa)
{
    t_philo *p;
    int     tmp;
    
	p = (t_philo *)pa;
    tmp = 0;
	
	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
	pthread_mutex_lock(&p->data->wait_all);
	pthread_mutex_unlock(&p->data->wait_all);
	
	pthread_mutex_lock(&p->data->pr_order);
	if (p->data->order == 0)
		p->data->order = p->num_philo;
	pthread_mutex_unlock(&p->data->pr_order);
	pthread_mutex_lock(&p->data->pr_print);
	pthread_mutex_lock(&p->data->pr_order);
	ft_itoa(p->data->order, p->data->str);
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
	pthread_mutex_unlock(&p->data->pr_order);
	pthread_mutex_unlock(&p->data->pr_print);

	while (tmp == 0)
	{
		if (p->data->order % 2 == p->num_philo % 2)
			;
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
		usleep(200);
	}
    pthread_mutex_lock(&p->data->pr_data_table);
	p->data->table--;
	pthread_mutex_unlock(&p->data->pr_data_table);
	return (NULL);
}

int	die_philo_odd(t_data_philo *p, int stop_check)
{
	int	i;
	unsigned long time;
	//int				eat;

	//eat = 0;
	i = -1;
	if (stop_check > 0)
		return (1);
	
	while (++i < p->nbr_philo)
	{
		time = time_now();
		pthread_mutex_lock(&p->pr_time);
		if (time - p->time_begin >=  (unsigned long)p->t_die
			&& time - p->philo[i].last_meal >= (unsigned long)p->t_die)
		{
			pthread_mutex_unlock(&p->pr_time);
			pthread_mutex_lock(&p->pr_data_die);
			p->die = 1;
			pthread_mutex_unlock(&p->pr_data_die);
			pthread_mutex_lock(&p->pr_print);
			str_join(p->str, "\e[15;31mtimestamp: ");
			ft_itoa(time - p->time_begin, p->str);
			str_join(p->str, "  ");
			ft_itoa(p->philo[i].num_philo, p->str);
			str_join(p->str, " died\e[0m\n");
			ft_putstr(p->str);
			ft_bzero(p->str);
			pthread_mutex_unlock(&p->pr_print);
			return (1);
		}
		pthread_mutex_unlock(&p->pr_time);
		//if (p->philo[i].have_eating_max == 1)
		//	eat++;
    }
    /*if (eat == p->nbr_philo)
	{
		pthread_mutex_lock(&p->pr_data);
	    p->die = 1;
		pthread_mutex_unlock(&p->pr_data);
	    return (1);
    }*/
    return (0);
}

int philo_odd(t_data_philo *p)
{
    int i;
    int tmp;
    int tmp2;
    
    tmp2 = 0;
    p->table = p->nbr_philo;
	tmp = p->table;
    i = -1;
    if (p->t_philo_must_eat == 0)
		return (0);

	pthread_mutex_lock(&p->wait_all);
    while (++i < p->nbr_philo)
    {
        pthread_create(&p->philo[i].th, NULL, routine_odd,
            (void *)&p->philo[i]);
    }
	p->time_begin = time_now();
	pthread_mutex_unlock(&p->wait_all);
	
    while (tmp > 0)
	{
	    pthread_mutex_lock(&p->pr_data_table);	
		tmp = p->table;
		pthread_mutex_unlock(&p->pr_data_table);
		if (die_philo_odd(p, tmp2) == 1)
			tmp2 = 2;
	}

    i = -1;
    while (++i < p->nbr_philo)
        pthread_join(p->philo[i].th, NULL);          
    return (0);
}
