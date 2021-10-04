/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_odd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 22:35:53 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 01:53:26 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_odd(void *pa)
{
    t_philo *p;
    int     tmp;
    
	p = (t_philo *)pa;
    tmp = p->data->die;

	pthread_mutex_lock(&p->data->pr_time);
	p->last_meal = time_now();
	pthread_mutex_unlock(&p->data->pr_time);
	pthread_mutex_lock(&p->data->wait_all);
	pthread_mutex_unlock(&p->data->wait_all);
	
	pthread_mutex_lock(&p->data->pr_order);
	pthread_mutex_unlock(&p->data->pr_order);

	
	pthread_mutex_lock(&p->data->pr_order);
	if (p->data->pivot == 1)
	{
		p->data->pivot = 0;
		if (p->data->order == 0 && p->data->pivot == 0)
			p->data->order = p->num_philo;
		if (p->data->order2 == 0 && p->data->order % 2 != p->num_philo % 2)
			p->data->order2 = p->num_philo;
		pthread_mutex_unlock(&p->data->block_last_elem);
		pthread_mutex_unlock(&p->data->pr_order);
	}
	else
	{
		if (p->data->order == 0 && p->num_philo == p->data->nbr_philo)
		{
			p->data->pivot = 1;
		}
		if (p->data->order == 0 && p->data->pivot == 0)
			p->data->order = p->num_philo;
		if (p->data->order2 == 0 && p->data->order % 2 != p->num_philo % 2)
			p->data->order2 = p->num_philo;
		pthread_mutex_lock(&p->data->block_last_elem);
		if (p->data->pivot == 1)
		{
			pthread_mutex_unlock(&p->data->pr_order);
			pthread_mutex_lock(&p->data->block_last_elem);
			pthread_mutex_unlock(&p->data->block_last_elem);
		}
		else
		{
			pthread_mutex_unlock(&p->data->block_last_elem);
			pthread_mutex_unlock(&p->data->pr_order);
		}
	}
	

	if (p->num_philo == p->data->nbr_philo)
		usleep(5);
	while (tmp == 0)
	{			
		if (p->nbr_eat > 0)
		{
			if (((p->data->order % 2) == (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
			{
				pthread_mutex_lock(&p->data->pr_order);
				if (p->data->order == p->num_philo)
				{
					pthread_mutex_unlock(&p->data->pr_order);
					pthread_mutex_lock(&p->data->pr_temp);
				}
				else
					pthread_mutex_unlock(&p->data->pr_order);
				lock_unlock_mutex_wave_3(p);
			}
			if (((p->data->order % 2) != (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
			{
				lock_unlock_mutex_wave_3(p);
			}
		}
		
		if (((p->data->order % 2) == (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
		{
			lock_mutex_wave_1(p);
			// Mettre le code output
			take_fork_and_display(p);
			//p->last_meal = time_now();
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			// Mettre le code output
			//display_wave_1(p);
			usleep(p->eating * 1000);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
			unlock_mutex_wave_1(p);
		}
		else if (((p->data->order % 2) != (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
		{
			find_first_elem(p);
			pthread_mutex_lock(&p->data->pr_temp);
			pthread_mutex_unlock(&p->data->pr_temp);
			lock_mutex_wave_2(p);
			lock_unlock_mutex_wave_1(p);
			// Mettre le code output
			//take_fork_and_display(p);
			pthread_mutex_lock(p->right);
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			// Mettre le code output
			//display_wave_2(p);
			usleep(p->eating * 1000);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
			unlock_mutex_wave_2(p);
		}
		else
		{
			pthread_mutex_lock(&p->data->wave_3);
			lock_unlock_mutex_wave_2(p);
			lock_unlock_mutex_wave_1(p);
			// Mettre le code output
			take_fork_and_display2(p);
			pthread_mutex_lock(&p->data->pr_time);
			p->last_meal = time_now();
			pthread_mutex_unlock(&p->data->pr_time);
			display_eating_odd(p);
			// Mettre le code output
			//display_wave_3(p);
			usleep(p->eating * 1000);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(&p->data->wave_3);
		}
		p->nbr_eat++;
		display_sleeping_odd(p);
		usleep(p->sleeping * 1000);
		display_thinking_odd(p);
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
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
	int				eat;

	eat = 0;
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
		if (p->philo[i].have_eating_max == 1)
			eat++;
		pthread_mutex_unlock(&p->pr_time);
    }
    if (eat == p->nbr_philo)
	{
		pthread_mutex_lock(&p->pr_data_die);
	    p->die = 1;
		pthread_mutex_unlock(&p->pr_data_die);
	    return (1);
    }
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


		/*
		if (p->data->order % 2 != p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_2);
			if (p->num_philo == p->data->order2)
				pthread_mutex_lock(&p->data->wave_1);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;36m wave 2: num philo ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			if (p->num_philo == p->data->order2)
				pthread_mutex_unlock(&p->data->wave_3);
		}
		else if (p->data->order % 2 == p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_1);
			pthread_mutex_unlock(&p->data->wave_1);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;35m wave 1: num philo ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			if (p->num_philo == p->data->order)
			{
				pthread_mutex_unlock(&p->data->wave_2);
			}
		}
		else{
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_unlock(&p->data->wave_3);
			
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;33m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_1);
		}
		*/
		//else if (p->data->nbr_philo == p->num_philo)
		//{
		/*
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_2);
			usleep(1000);
			pthread_mutex_lock(&p->data->pr_print);
			ft_itoa(p->num_philo, p->data->str);
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);*/
		//}

		/*pthread_mutex_lock(&p->data->pr_order);
		if (p->data->order == p->num_philo)
			p->data->order = 0;
		if (p->data->order2 == p->num_philo)
			p->data->order2 = 0;
		pthread_mutex_unlock(&p->data->pr_order);*/

/*
		pthread_mutex_lock(&p->data->pr_temp);
		if (p->data->temp == 0)
		{
			pthread_mutex_lock(&p->data->wave_2);
			p->data->temp = 1;
		}
		pthread_mutex_unlock(&p->data->pr_temp);
		if (p->data->order % 2 == p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_1);
			pthread_mutex_unlock(&p->data->wave_1);
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;35m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_tour);
			p->data->tour++;
			if (p->data->tour == ((p->data->nbr_philo / 2) + (p->data->order % 2)))
			{
				p->data->tour = 0;
				pthread_mutex_unlock(&p->data->pr_tour);
				pthread_mutex_unlock(&p->data->wave_2);
				pthread_mutex_lock(&p->data->wave_1);
			}
			else
				pthread_mutex_unlock(&p->data->pr_tour);
		}
		else if (p->data->order % 2 != p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_2);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;36m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_tour);
			p->data->tour++;
			if (p->data->tour == ((p->data->nbr_philo / 2) + check))
			{
				p->data->tour = 0;
				pthread_mutex_unlock(&p->data->pr_tour);
				pthread_mutex_lock(&p->data->wave_2);
				pthread_mutex_unlock(&p->data->wave_3);
			}
			else
				pthread_mutex_unlock(&p->data->pr_tour);
		}
		else
		{
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_unlock(&p->data->wave_3);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;33m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_temp);
			p->data->temp = 0;
			pthread_mutex_unlock(&p->data->pr_temp);
			pthread_mutex_unlock(&p->data->wave_1);
		}
*/

/*

	pthread_mutex_lock(&p->data->pr_temp);
	if (p->data->temp == 0)
	{
		pthread_mutex_lock(&p->data->wave_2);
	}
	pthread_mutex_unlock(&p->data->pr_temp);
	while (tmp == 0)
	{
		pthread_mutex_lock(&p->data->pr_temp);
		if (p->data->temp == 0)
		{
			p->data->temp = 1;
			
			pthread_mutex_lock(&p->data->wave_3);
		}
		pthread_mutex_unlock(&p->data->pr_temp);


		if (p->data->order % 2 == p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_1);
			pthread_mutex_unlock(&p->data->wave_1);

			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;35m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_tour);
			p->data->tour++;
			if (p->data->tour == ((p->data->nbr_philo - 1) / 2))
			{
				p->data->tour = 0;
				pthread_mutex_unlock(&p->data->pr_tour);
				pthread_mutex_lock(&p->data->wave_1);
				pthread_mutex_unlock(&p->data->wave_2);
			}
			else
				pthread_mutex_unlock(&p->data->pr_tour);
		}
		else if (p->data->order % 2 != p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_2);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;36m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_tour);
			p->data->tour++;
			if (p->data->tour == ((p->data->nbr_philo - 1) / 2))
			{
				p->data->tour = 0;
				pthread_mutex_lock(&p->data->wave_2);
				pthread_mutex_unlock(&p->data->wave_3);
				pthread_mutex_unlock(&p->data->pr_tour);
			}
			else
				pthread_mutex_unlock(&p->data->pr_tour);
		}
		else
		{
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_unlock(&p->data->wave_3);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;33m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
			pthread_mutex_lock(&p->data->pr_temp);
			p->data->temp = 0;
			pthread_mutex_unlock(&p->data->pr_temp);
			pthread_mutex_unlock(&p->data->wave_1);
			
		}
		usleep(10000);
		p->nbr_eat++;
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);
	}
    pthread_mutex_lock(&p->data->pr_data_table);
	p->data->table--;
	pthread_mutex_unlock(&p->data->pr_data_table);
	return (NULL);
}


*/



/*
	if (p->data->order % 2 == p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_1);
			pthread_mutex_unlock(&p->data->wave_1);
			

			
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;35m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);

			pthread_mutex_lock(&p->data->pr_order);
			if (p->data->order == p->num_philo)
			{
				pthread_mutex_unlock(&p->data->pr_order);
				
				pthread_mutex_unlock(&p->data->wave_2);
				pthread_mutex_unlock(&p->data->wave_3);
			}
			else
				pthread_mutex_unlock(&p->data->pr_order);
		}
		else if (p->data->order % 2 != p->num_philo % 2 && p->num_philo != p->data->nbr_philo)
		{
			pthread_mutex_lock(&p->data->wave_2);
			pthread_mutex_unlock(&p->data->wave_2);

			pthread_mutex_lock(&p->data->pr_tour);
			p->data->tour++;
			pthread_mutex_lock(&p->data->pr_order);
			if (p->data->tour == 1)
				p->data->order2 = p->num_philo;
			pthread_mutex_unlock(&p->data->pr_order);
			pthread_mutex_unlock(&p->data->pr_tour);

			pthread_mutex_lock(&p->data->pr_order);
			if (p->data->order2 == p->num_philo)
			{
				pthread_mutex_unlock(&p->data->pr_order);
				pthread_mutex_lock(&p->data->wave_1);
				pthread_mutex_lock(&p->data->wave_3);
			}
			else
				pthread_mutex_unlock(&p->data->pr_order);

			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;36m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);

			usleep(p->eating * 1000);
			
			pthread_mutex_lock(&p->data->pr_order);
			if (p->data->order2 == p->num_philo)
			{
				pthread_mutex_unlock(&p->data->pr_order);
				pthread_mutex_unlock(&p->data->wave_3);
				pthread_mutex_unlock(&p->data->wave_1);
			}
			else
				pthread_mutex_unlock(&p->data->pr_order);
		}
		else
		{
			pthread_mutex_lock(&p->data->wave_3);
			pthread_mutex_unlock(&p->data->wave_3);
			pthread_mutex_lock(&p->data->pr_print);
			str_join(p->data->str, "\e[0;33m ");
			ft_itoa(p->num_philo, p->data->str);
			str_join(p->data->str, "\e[0m");
			ft_putstr(p->data->str);
			ft_bzero(p->data->str);
			pthread_mutex_unlock(&p->data->pr_print);
			usleep(p->eating * 1000);
		}
		usleep(p->sleeping * 1000);
		p->nbr_eat++;
		pthread_mutex_lock(&p->data->pr_data_die);
		tmp = p->data->die;
		pthread_mutex_unlock(&p->data->pr_data_die);

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


*/

		/*if (p->data->temp == 0 && ((p->data->order % 2) == (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
			p->data->temp = 1;
		if (p->data->temp == 1 && ((p->num_philo % 2) != (p->data->order % 2)))
			p->data->temp = 2;
		if (p->data->temp == 1 && ((p->num_philo) == (p->data->nbr_philo)))
			p->data->temp = 0;
		usleep(p->sleeping * 1000);
		if (((p->data->order % 2) == (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
			usleep((p->eating * 2000) - (p->sleeping * 1000));
		if (((p->data->order % 2) != (p->num_philo % 2)) && (p->num_philo != p->data->nbr_philo))
			usleep((p->eating * 1000) - (p->sleeping * 1000));*/
