/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 02:43:48 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/27 03:08:01 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_fork_right(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	if (p->data->die != 0)
		return ;
	str_join(p->data->str, "\e[11;32mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " has taken a fork right\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
}

void	display_fork_left(t_philo *p)
{
	unsigned long	time;

	time = time_now();
	if (p->data->die != 0)
		return ;
	str_join(p->data->str, "\e[1;32mtimestamp: ");
	ft_itoa(time - p->data->time_begin, p->data->str);
	str_join(p->data->str, "  ");
	ft_itoa(p->num_philo, p->data->str);
	str_join(p->data->str, " has taken a fork left\e[0m\n");
	ft_putstr(p->data->str);
	ft_bzero(p->data->str);
}
