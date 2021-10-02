/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:41:06 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/02 18:24:25 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_other_finnish(t_philo *p, int x)
{
    int tmp;
    
    pthread_mutex_lock(&p->data->pr_temp);
    if (p->data->temp != x)
    {
        tmp = p->data->temp;
        pthread_mutex_unlock(&p->data->pr_temp);
		while (tmp != x)
		{
            pthread_mutex_lock(&p->data->pr_temp);
			tmp = p->data->temp;
			pthread_mutex_unlock(&p->data->pr_temp);
		}
    }
    else
	    pthread_mutex_unlock(&p->data->pr_temp);
}

void	change_value_temp1(t_philo *p)
{			
	pthread_mutex_lock(&p->data->pr_temp);
	if (p->data->temp == 0)
    	p->data->temp = 1;
    pthread_mutex_unlock(&p->data->pr_temp);
}

void    change_value_temp2(t_philo *p)
{			
	pthread_mutex_lock(&p->data->pr_temp);
	if (p->data->temp == 1)
    	p->data->temp = 2;
    pthread_mutex_unlock(&p->data->pr_temp);
}

void    change_value_temp3(t_philo *p)
{
    pthread_mutex_lock(&p->data->pr_temp);
	if (p->data->temp == 2)
    	p->data->temp = 0;
    pthread_mutex_unlock(&p->data->pr_temp);
}
