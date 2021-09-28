# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 02:02:11 by rkhelif           #+#    #+#              #
#    Updated: 2021/09/28 18:10:30 by rkhelif          ###   ########.fr        #
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
		ft_check.c \
		routine.c \
		next.c \
		itoa.c \
		one_philo.c \
		philo_pair.c \
		display.c\
		philo_odd.c

OBJS = ${addprefix ${DIR_OBJ}/,${SRCS:.c=.o}}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} 
all:${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME} 
#-lpthread

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	[ -d $(DIR_OBJ) ] || mkdir -p $(DIR_OBJ)
	${CC} $(FLAGS) -I ${DIR_INC} -c $< -o $@ 
#-lpthread
clean:
	${RM} ${OBJS}
	${RM} ${DIR_OBJ}

fclean : clean
	${RM} ${NAME}
re: fclean all
