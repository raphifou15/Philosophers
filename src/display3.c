/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:35:39 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 17:51:26 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_die_odd(t_data_philo *p, unsigned long time, int i)
{
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
}
