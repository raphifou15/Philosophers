/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:11:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/22 01:20:07 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data_philo *p, char **argv)
{
	p->nbr_philo = ft_atoi_m(argv[1]);
	if (p->nbr_philo == -1)
		return (1);
	p->t_die = ft_atoi_m(argv[2]);
	if (p->t_die == -1)
		return (1);
	p->t_eat = ft_atoi_m(argv[3]);
	if (p->t_eat == -1)
		return (1);
	p->t_sleep = ft_atoi_m(argv[4]);
	if (p->t_sleep == -1)
		return (1);
	if (argv[5] == NULL)
		p->t_philo_must_eat = -2;
	else
	{
		p->t_philo_must_eat = ft_atoi_m(argv[5]);
		if (p->t_philo_must_eat == -1)
			return (1 + err_msg(5));
	}
	p->die = 0;
	return (0);
}

int	init_philo_part2(t_data_philo *p)
{
	int	i;

	i = -1;
	p->philo = malloc(sizeof(t_philo) * p->nbr_philo);
	if (p->philo == NULL)
		return (1 + err_msg(5) + ft_free(p));
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nbr_philo);
	if (p->forks == NULL)
		return (1 + err_msg(5) + ft_free(p));
	while (++i < p->nbr_philo)
		pthread_mutex_init(&p->forks[i], NULL);
	pthread_mutex_init(&p->mutex, NULL);
	init_philo_part3(p);
	return (0);
}

void	init_philo_part3(t_data_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->nbr_philo)
	{
		if (p->t_philo_must_eat == 0)
			p->philo[i].have_eating_max = 1;
		else
			p->philo[i].have_eating_max = 0;
		p->philo[i].data = p;
		p->philo[i].die = 0;
		p->philo[i].mutex = &p->mutex;
		p->philo[i].eating = (unsigned long)p->t_eat;
		p->philo[i].sleeping = (unsigned long)p->t_sleep;
		p->philo[i].num_philo = i + 1;
		p->philo[i].die = p->t_die;
		p->philo[i].nbr_eat = 0;
		p->philo[i].right = &p->forks[i];
		if (i + 1 == p->nbr_philo)
			p->philo[i].left = &p->forks[0];
		else
			p->philo[i].left = &p->forks[i + 1];
	}
}

int	ft_philosophers(t_data_philo *p, int i)
{
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
		p->philo[i].last_meal = time_now();
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = 0;
	while (++i < p->nbr_philo)
	{
		usleep(200);
		if (pthread_create(&p->philo[i].th, NULL, routine,
				(void *)&p->philo[i]) != 0)
			return (1 + destroy_mutex(p) + ft_free(p) + err_msg(6));
		++i;
	}
	i = -1;
	while (++i < p->nbr_philo)
		pthread_join(p->philo[i].th, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data_philo	p;

	if (check_error(argc, argv) != 0)
		return (1);
	if (init_philo(&p, argv) != 0)
		return (1);
	if (init_philo_part2(&p) != 0)
		return (1);
	if (ft_philosophers(&p, -1) != 0)
		return (1);
	destroy_mutex(&p);
	ft_free(&p);
	return (0);
}
