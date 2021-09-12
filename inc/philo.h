/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:07:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/12 04:46:05 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	check_error(int argc, char **argv);
int	check_argv_are_number(int argc, char **argv);
int	err_msg(int err);

void ft_putstr_err(char *str);


#endif
