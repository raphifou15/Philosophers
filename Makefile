# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 02:02:11 by rkhelif           #+#    #+#              #
#    Updated: 2021/10/06 05:22:36 by rkhelif          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = philo
RM = rm -rf
DIR_OBJ = other
DIR_SRC = src
DIR_INC = inc

SRCS = 	main.c \
		philosophers.c \
		error.c \
		utilities.c \
		ft_free.c \
		routine.c \
		itoa.c \
		one_philo.c \
		philo_pair.c \
		philo_pair2.c \
		display.c\
		display2.c\
		display3.c\
		lock_mutex.c\
		lock_mutex2.c\
		lock_unlock.c\
		find_first_elem.c\
		philo_odd.c\
		philo_odd_routine.c\
		wait_elem_routine.c\
		loop_odd.c\
		routine_pair2.c

OBJS = ${addprefix ${DIR_OBJ}/,${SRCS:.c=.o}}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -lpthread
all:${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME} -lpthread

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	[ -d $(DIR_OBJ) ] || mkdir -p $(DIR_OBJ)
	${CC} $(FLAGS) -I ${DIR_INC} -c $< -o $@

clean:
	${RM} ${OBJS}
	${RM} ${DIR_OBJ}

fclean : clean
	${RM} ${NAME}
re: fclean all
