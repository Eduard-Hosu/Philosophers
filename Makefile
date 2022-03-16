# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 18:22:39 by ehosu             #+#    #+#              #
#    Updated: 2022/03/16 18:01:58 by ehosu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = phil.h
SRCS = phil.c helpers/get_data_helpers.c helpers/helpers.c helpers/activity.c
OBJS = ${SRCS:.c=.o}
RM = rm -rf

CC = gcc
# -pthread
# -lpthread
# -fsanitize=thread
CFLAGS = -g -pthread -Wall -Wextra -Werror

all:	$(NAME)

%.o: %.c
	$(CC) -pthread -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJS)
	$(CC) -pthread -o $(NAME) $(CFLAGS) $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} $(NAME)

re:	fclean all

.PHONY:
	all clean fclean re