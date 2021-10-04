/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:24:18 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/03 22:42:41 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_wave_1(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;35m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_wave_2(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;36m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}

void	display_wave_3(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_print);
    str_join(p->data->str, "\e[0;33m ");
    ft_itoa(p->num_philo, p->data->str);
    str_join(p->data->str, "\n\e[0m");
    ft_putstr(p->data->str);
    ft_bzero(p->data->str);
    pthread_mutex_unlock(&p->data->pr_print);
}